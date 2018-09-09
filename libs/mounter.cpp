#include "ncurses.h"
#include "mounter.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>
#include <vector>
#include <sstream>


using namespace std;

string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != nullptr)
            result += buffer.data();
    }
    return result;
}
string& ltrim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

string& rtrim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

string& trim(string& str, const string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

Mounter::Mounter(int term_width, int term_height){
    Mounter::choice(7,35, term_height/2-3, term_width/2-17);
}
void Mounter::choice(int height, int width, int starty, int startx){
    int num_choices = 2;
    string choices[2] {"MOUNT", "UNMOUNT"};
    string title = "Choose action";
    int response;
    response = d.fetch_response(title, height, width, starty, startx, choices, num_choices);
    if ( response == 0 ){
        Mounter::mount(height, width, starty, startx);
    } else if ( response == 1 ){
        Mounter::umount(height, width, starty, startx);
    }
}
void Mounter::mount(int height, int width, int starty, int startx){
    // GET DEVICE
    string devices = exec("lsblk -p -l | grep part | grep -e 'part $' | awk '{print $1}' | tr '\n' ' ' | sed 's/,$//'");
    vector<string> device_vector;
    stringstream ss(devices);
    string temp;
    while (ss >> temp)
    device_vector.push_back(temp);

    string device_arr[device_vector.size()];
    for ( int i=0; i < device_vector.size(); i++ ){
        device_arr[i] = device_vector[i];
    }

    string title = "Select device";
    d.clear();
    int device_id = d.fetch_response(title, height, width, starty, startx, device_arr, device_vector.size());
    if ( device_id == -1 ) return;
    // GET DEVICE

    // GET MOUNTPOINT
    string mount_points = exec("find /mnt -maxdepth 1 -type d -empty | tr '\n' ' ' | sed 's/.$//'");
    vector<string> mntp_vector;
    stringstream ss2(mount_points);
    while (ss2 >> temp)
    mntp_vector.push_back(temp);

    string mntp_arr[mntp_vector.size()];
    for ( int i=0; i < mntp_vector.size(); i++ ){
        mntp_arr[i] = mntp_vector[i];
    }

    title = "Select mountpoint";
    d.clear();
    int mntp_id = d.fetch_response(title, height, width, starty, startx, mntp_arr, mntp_vector.size());
    if ( mntp_id == -1 ) return;
    // GET MOUNTPOINT

    // MOUNT
    string mount_command = "mount " + device_arr[device_id] + " " + mntp_arr[mntp_id];
    exec(mount_command.c_str());
    // MOUNT
    cout << "Mounted device " << trim(device_arr[device_id]) << " to mountpoint " << trim(mntp_arr[mntp_id]);
}

void Mounter::umount(int height, int width, int starty, int startx){
    string used_mount_points = exec("lsblk -p -l | grep part | grep -v boot/efi | grep -v -e 'part /$' | grep -v SWAP | grep 'part /' | awk '{print $7}' | tr '\n' ' ' | sed 's/.$//'");
    vector<string> mntp_vector;
    stringstream ss(used_mount_points);
    string temp;
    while (ss >> temp)
    mntp_vector.push_back(temp);

    string mntp_arr[mntp_vector.size()];
    for ( int i=0; i < mntp_vector.size(); i++ ){
        mntp_arr[i] = mntp_vector[i];
    }

    string title = "Select mountpoint";
    d.clear();
    int mntp_id = d.fetch_response(title, height, width, starty, startx, mntp_arr, mntp_vector.size());
    if ( mntp_id == -1 ) return;

    string mount_command = "umount " + mntp_arr[mntp_id];
    exec(mount_command.c_str());
}
