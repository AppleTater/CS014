#include "Playlist.h"

#include <iostream>
using namespace std;

void PrintMenu(string);

int main() {
    string title = "";
    
    cout << "Enter playlist's title:" << endl << endl;
    getline(cin, title);
    
    PrintMenu(title);
    
    return 0;
}

void PrintMenu(string title) {
    char option = ' ';
    string uniqueID = "";
    string songName = "";
    string artistName = "";
    int songLength = 0;
    int currPos = 0;
    int newPos = 0;
    int numIter = 0;
    int max = 0;
    PlaylistNode* playlist = nullptr;
    PlaylistNode* head = nullptr;
    PlaylistNode* tail = nullptr;
    PlaylistNode* temp = nullptr;
    PlaylistNode* at = nullptr;
    
    while (option != 'q') {
        
        option = ' ';
    
        while (!(option == 'a' || option == 'd' || option == 'c' || option == 's' || option == 't' || option == 'o' || option == 'q')) {
            cout << title << " PLAYLIST MENU" << endl
                 << "a - Add song" << endl
                 << "d - Remove song" << endl
                 << "c - Change position of song" << endl
                 << "s - Output songs by specific artist" << endl
                 << "t - Output total time of playlist (in seconds)" << endl
                 << "o - Output full playlist" << endl
                 << "q - Quit" << endl << endl
                 << "Choose an option:";
            cin >> option;
            cout << endl;
            cin.ignore(1);
        }
        
        if (option == 'a') {
            cout << "ADD SONG" << endl
                 << "Enter song's unique ID:" << endl;
            getline(cin, uniqueID);
            cout << "Enter song's name:" << endl;
            getline(cin, songName);
            cout << "Enter artist's name:" << endl;
            getline(cin, artistName);
            cout << "Enter song's length (in seconds):" << endl;
            cin >> songLength;
            cout << endl;
            
            at = new PlaylistNode(uniqueID, songName, artistName, songLength);
            
            if (head == nullptr) {
                head = at;
                tail = at;
            }
            else {
                temp = tail;
                tail = at;
                temp->SetNext(at);
            }
        }
        else if (option == 'd') {
            cout << "REMOVE SONG" << endl
                 << "Enter song's unique ID:" << endl;
            getline(cin, uniqueID);
            
            at = head;
            temp = at;
            
            while (at != nullptr) {
                if (at->GetID() == uniqueID) {
                    songName = at->GetSongName();
                    if (head == at) {
                        if (head == tail) {
                            tail = nullptr;
                        }
                        temp = head;
                        head = at->GetNext();
                        delete temp;
                        at = head;
                        temp = at;
                    }
                    else {
                        if (tail == at) {
                            tail = temp;
                        }
                        
                        temp->SetNext(at->GetNext());
                        delete at;
                        at = temp;
                        at = at->GetNext();
                        
                    }
                    cout << "\"" << songName << "\" removed." << endl << endl;
                }
                else {
                    temp = at;
                    at = at->GetNext();
                }
            }
        }
        else if (option == 'c') {
            cout << "CHANGE POSITION OF SONG" << endl
                 << "Enter song's current position:" << endl;
            cin >> currPos;
            cout << "Enter new position for song:" << endl;
            cin >> newPos;
            
            at = head;
            temp = head;
            max = currPos;
            
            numIter = 1;
            
            while (numIter < currPos) {
                temp = at;
                at = at->GetNext();
                ++numIter;
            }
            
            songName = at->GetSongName();
            
            if (head == at) {
                head = at->GetNext();
            }
            else if (tail == at) {
                temp->SetNext(tail->GetNext());
                tail = temp;
            }
            else {
                temp->SetNext(at->GetNext());
            }
            
            temp = head;
            numIter = 2;
            
            while (numIter < newPos) {
                temp = temp->GetNext();
                ++numIter;
            }
            
            if (newPos <= 1) {
                at->SetNext(head);
                head = at;
            }
            else if (newPos > (max - 1)) {
                tail = at;
                temp->InsertAfter(at);
            }
            else {
                temp->InsertAfter(at);
            }
            cout << "\"" << songName << "\" moved to position " << newPos << endl << endl;
        }
        else if (option == 's') {
            cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl
                 << "Enter artist's name:" << endl;
            getline(cin, artistName);
            cout << endl;
            
            at = head;
            numIter = 1;
            
            while (at != nullptr) {
                if (at->GetArtistName() == artistName) {
                    cout << numIter << "." << endl;
                    playlist->PrintPlaylistNode(at);
                }
                at = at->GetNext();
                ++numIter;
            }
        }
        else if (option == 't') {
            cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl
                 << "Total time: " ;
            
            at = head;
            songLength = 0;
            
            while (at != nullptr) {
                songLength += at->GetSongLength();
                at = at->GetNext();
            }
            
            cout << songLength << " seconds" << endl << endl;
        }
        else if (option == 'o') {
            at = head;
            numIter = 0;
            
            cout << title << " - OUTPUT FULL PLAYLIST" << endl;
            
            if (head == nullptr) {
                cout << "Playlist is empty" << endl << endl;
            }
            else {
                while (at != nullptr) {
                    ++numIter;
                    cout << numIter << "." << endl;
                    playlist->PrintPlaylistNode(at);
                    at = at->GetNext();
                }
            }
        }
    }
}
