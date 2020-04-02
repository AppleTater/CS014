//Done using help from Professor LePendu <3
//Done possibly with the loving help of Hannah Bach <3 hbach003
//Done with help from Roy Feng rfeng016

#include <iostream>
#include <iomanip>

#include "Playlist.h"

using namespace std;

void PrintMenu(const string playlistTitle);

int main() {
   string playlistTitle;
   // Prompt user for playlist title
   cout << "Enter playlist's title:" << endl;
   getline(cin, playlistTitle);
   cout << endl;
   // Output play list menu options
   PrintMenu(playlistTitle);
   return 0;
}

void PrintMenu(const string playlistTitle) {
   char menuOp = ' ';
   string uniqueID;
   string songName;
   string artistName;
   int songLength = 0;
  //  int numNodes = 0;
   int songPosition = 0;
  //  int newPosition = 0;
  //  int totalTime;
  //  PlaylistNode* newSong = 0;
  //  PlaylistNode* currNode = 0;
  //  PlaylistNode* songNode = 0;
  //  PlaylistNode* prevNode = 0;
  //  PlaylistNode* insertPosNode = 0;
   PlaylistNode* headNode = 0;
   PlaylistNode* tailNode = 0;
  //  PlaylistNode* currPrintNode = 0;
   // Output menu option, prompt users for valid selection
   while(menuOp != 'q') {
      menuOp = ' ';
      cout << playlistTitle << " PLAYLIST MENU" << endl;
      cout << "a - Add song" << endl;
      cout << "d - Remove song" << endl;
      cout << "c - Change position of song" << endl;
      cout << "s - Output songs by specific artist" << endl;
      cout << "t - Output total time of playlist (in seconds)" << endl;
      cout << "o - Output full playlist" << endl;
      cout << "q - Quit" << endl << endl;
      while (menuOp != 'a' && menuOp != 'd' && menuOp != 'c' &&
             menuOp != 's' && menuOp != 't' && menuOp != 'o' && menuOp != 'q') {
         cout << "Choose an option:" << endl;
         cin >> menuOp;
      }
      // Call corresponding menu action
      
      if (menuOp == 'a') {
        // Prompt user for song information
        cout << "ADD SONG" << endl;

        cout << "Enter song's unique ID:" << endl;
        cin >> uniqueID;

        cout << "Enter song's name:" << endl;
        cin.ignore();
        getline (cin, songName);

        cout << "Enter artist's name:" << endl;
        getline(cin, artistName);

        cout << "Enter song's length (in seconds):" << endl;
        cin >> songLength;
        cout << endl;

        PlaylistNode *song = new PlaylistNode (uniqueID, songName, artistName, songLength);

        if (headNode == nullptr) {
          headNode = song;
        }

        else {
          PlaylistNode *temp = headNode;

          while (temp->GetNext() != NULL) {
            temp = temp->GetNext();
          }

          temp->InsertAfter(song);
        }
      }

      if (menuOp == 'd') {
        cout << "REMOVE SONG" << endl;

        cout << "Enter song's unique ID:" << endl;
        cin >> uniqueID;

        PlaylistNode *previous = nullptr;
        PlaylistNode *current = headNode;

        while (current && current->GetID() != uniqueID) {
          previous = current;
          current = current->GetNext();
        }

        if (current) {
          if (previous) {
            previous->SetNext(current->GetNext());
          }

          else {
            headNode = current->GetNext();
          }

          if (!current->GetNext()) {
            tailNode = previous;
          }

          cout << current;
        }
      }

      if (menuOp == 'c') {
        int newPos = 0;

        cout << "CHANGE POSITION OF SONG" << endl;

        cout << "Enter song's current position:" << endl;
        cin >> songPosition;

        cout << "Enter new position for song:" << endl;
        cin >> newPos;

        PlaylistNode *previous = NULL;
        PlaylistNode *current = headNode;

        if (headNode == nullptr || headNode == tailNode) {
          cout << "Playlist is empty." << endl << endl;
        }

        for (int i = 1; current != nullptr && i < songPosition; i++) {
          previous = current;
          current = current->GetNext();
        }

        if (current != nullptr) {
          string currentSong = current->GetSongName();
          if (previous == nullptr) {
            headNode = current->GetNext();
          }

          else {
            previous->SetNext(current->GetNext());
          }

          if (current == tailNode) {
            tailNode = previous;
          }

          PlaylistNode *ins = current;
          previous = nullptr;
          current = headNode;

          for (int i = 1; current != nullptr && i < newPos; i++) {
            previous = current;
            current = current->GetNext();
          }

          if (previous == nullptr) {
            ins->SetNext(headNode);
            headNode = ins;
          }

          else {
            ins->InsertAfter(previous);
          }

          if (current == nullptr) {
            tailNode = ins;
          }

          cout << '\"' << currentSong << "\" moved to position" << newPos << endl;
        }

        else {
          cout << "Position invalid" << endl;
        }
      }

      if (menuOp == 's') {
        cout << "OUTPUT SONGS BY SPECIFIC ARTIST" << endl <<  "Enter artist's name:" << endl;
        getline (cin, artistName);

        PlaylistNode *current = headNode;
        int iter = 1;

        while (current != nullptr) {
          if (current->GetArtistName() == artistName) {
            cout << iter << "." << endl;
            
          }
        }

        

      }

      if (menuOp == 't') {
        cout << "OUTPUT TOTAL TIME OF PLAYLIST (IN SECONDS)" << endl;

        int total = 0;

        if (headNode == nullptr) {
          cout << "Playlist is empty" << endl;
        }

        else {
          PlaylistNode *temp = headNode;

          while(temp != nullptr) {
            total = total + temp->GetSongLength();
            temp = temp->GetNext();
          }

          cout << "Total time: " << total << endl;
        }
      }
      

      if (menuOp == 'o') {
        cout << playlistTitle << " - OUTPUT FULL PLAYLIST" << endl;
        
        if (headNode == nullptr) {
          cout << "Playlist is empty" << endl << endl;
        }
      
        else {
          int counter = 1;
          PlaylistNode *node = headNode;

          while (node != nullptr) {
            cout << counter << ".\n";
            node->PrintPlaylistNode();

            counter ++;
            node = node->GetNext();
          }
        }
      } 
   }
}
