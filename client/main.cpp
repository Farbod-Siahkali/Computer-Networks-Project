#include "client.h"

using namespace std;

//Client side
int main(int argc, char *argv[])
{
    if(argc != 3)
    {
       cerr << "Usage: ip_address port" << endl; exit(0); 
    }
    const char *serverIp = strtok(argv[1], ":");
    int serverPort = atoi((const char*)strtok(0, ""));
    const char* userName = &argv[2][0];
   
    cout << "serverIp: " << serverIp << endl;
    cout << "serverPort: " << serverPort << endl;
    cout << "userName: " << userName << endl;

    auto clientSd = setup(serverIp, serverPort);
    connect_socket(clientSd, userName);
    
    struct timeval start1, end1;
    gettimeofday(&start1, NULL);
    vector<uint16_t> users;
    vector<string> user_names;
    uint16_t id;

    while(1) {
        fd_set read_fds;
        FD_ZERO (&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);
        auto tv = timeval{5, 0};
        auto ret = select(2, &read_fds, NULL, NULL, &tv);
        if (ret < 0)
            throw runtime_error("selct error");

        if (ret == 0) {
            auto tv_read = timeval{1, 0};
            setsockopt(clientSd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv_read, sizeof tv_read);
            recieve_message(clientSd, users, user_names, id);
        }
        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            cout << ">> ";
            string line;
            if (!getline(cin, line) || line == "exit" || line == "Exit") {
                clog<<"Exit!"<<endl; 
                break;
            }
            string input_temp, input_array[5];  
            stringstream input_data_stream(line);
            int i = 0;
            while (getline(input_data_stream, input_temp, ' ')) {
                input_array[i] = input_temp;
                i++;
                if(i>3) {
                    break;
                }
            }
            if(input_array[0] == "list"|| input_array[0] == "List") {
                cout << "Users:" << endl;
                list_users(clientSd,users,user_names,id);
                for (int i = 0; i<user_names.size(); i++) {
                    cout << "\t-" << user_names[i] << endl;
                }
            }
            else if (input_array[0] == "send"|| input_array[0] == "Send") {
                send_message(user_names,input_array,users,clientSd);
            }
            else {
                cout<<"Invalid Operation!"<<endl; 
            }
        }
    }

    gettimeofday(&end1, NULL);
    cout << "********Session********" << endl;
    cout << "Elapsed time: " << (end1.tv_sec- start1.tv_sec) 
      << " secs" << endl;
    cout << "Connection closed" << endl;
    return EXIT_SUCCESS;    
}