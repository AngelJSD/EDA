#include "Options.h"
#include "MidiFile.h"

#include <iostream>
#include <vector>

using namespace std;

Options  options;
int      quarterQ = 0;  // used with -q option: time units in quarter notes.
int      joinQ    = 0;  // used with -j option: join tracks before printing.
int      secondsQ = 0;  // used with -s option: print times in seconds.


void     checkOptions        (Options& opts);
void     example             (void);
void     usage               (const string& command);

int abs(int a){
    
    if(a<0)
      return a*-1;
    return a;
}

int distancia(vector<int> s1, vector<int> s2){

	int N1 = s1.size();
	int N2 = s2.size();
	int i, j;
	vector<int> T1(N2+1);

	for ( i = 0; i <= N2; i++ ){
		T1[i] = i;
	}

	for ( i = 0; i < N1; i++ ){
		T1[0] = i+1;
		int corner = i;
		for ( j = 0; j < N2; j++ )
	 	{
		  	int upper = T1[j+1];
			if ( s1[i] == s2[j] ){
				T1[j+1] = corner;
			}
			else{
				T1[j+1] = min(T1[j], min(upper, corner)) + 1;
			}
		corner = upper;
		}
	}
	return T1[N2];
}


int main(int argc, char** argv) {
   /*options.setOptions(argc, argv);
   //checkOptions(options);
   options.define("q|quarter=b", "Display ticks in quarter note units");
   options.define("j|join=b",    "Join tracks before printing");
   options.define("s|seconds=b", "Display times in seconds");

   options.define("author=b",   "Author of the program");
   options.define("version=b",  "Version of the program");
   options.define("example=b",  "Example useage of the program");
   options.define("h|help=b",   "List of options for the program");
   options.process();

   if (options.getBoolean("author")) {
      cout << "Written by Craig Stuart Sapp, "
              "craig@ccrma.stanford.edu, February 2015" << endl;
      exit(0);
   } else if (options.getBoolean("version")) {
      cout << "duration, version 1.0 (19 Feb 2015)\n"
              "compiled: " << __DATE__ << endl;
      exit(0);
   }

   quarterQ  = options.getBoolean("quarter");
   joinQ     = options.getBoolean("join");
   secondsQ  = options.getBoolean("seconds");

   if (secondsQ) {
      quarterQ = 0;
   }

   if (options.getArgCount() > 2) {
      cerr << "Error: One input file or standard input is required." << endl;
      exit(1);
   }*/

   vector<int> vect1,vect1t,vect2,vect2t;
   
   MidiEvent* mev;
   int duration;
   int status;
   MidiFile midifile, midifile1;
   
   if (secondsQ) {
      midifile.doTimeAnalysis();
   }
   
   //if (options.getArgCount()) {
      status = midifile.read(argv[1]);
   /*} else {
      status = midifile.read(cin);
   }*/
   
   //if (options.getArgCount()) {
      status = midifile1.read(argv[2]);
   /*} else {
      status = midifile1.read(cin);
   }*/
   if (status == 0) {
      cerr << "Error: could not read MIDI file" << endl;
      exit(1);
   }
   
   int tpq = midifile.getTicksPerQuarterNote();
   int tpq1 = midifile1.getTicksPerQuarterNote();
   int cont=0;
   int cont1=0;
   midifile.linkNotePairs();
   midifile1.linkNotePairs();
   
   midifile.joinTracks();
   midifile1.joinTracks();
   
   int track = 0;
   
   for (int i=0; i<midifile[track].size(); i++) {
     
      if (!midifile[track][i].isNoteOn()) {
         continue;
      }
      if (secondsQ) {
            duration = midifile[track][i].getDurationInSeconds();
         } else {
            duration = midifile[track][i].getTickDuration();
         }

         if (secondsQ) {
            vect1t.push_back(duration);
         } else if (quarterQ) {
            vect1t.push_back(duration/tpq);
         } else {
            vect1t.push_back(duration);
         }
      vect1.push_back((int)midifile[track][i][1]);
      cont++;
   }
   
   track = 0;
   
   for (int i=0; i<midifile1[track].size(); i++) {
     
      if (!midifile1[track][i].isNoteOn()) {
         continue;
      }
      if (secondsQ) {
            duration = midifile1[track][i].getDurationInSeconds();
         } else {
            duration = midifile1[track][i].getTickDuration();
         }

         if (secondsQ) {
            vect2t.push_back(duration);
         } else if (quarterQ) {
            vect2t.push_back(duration/tpq1);
         } else {
            vect2t.push_back(duration);
         }
      vect2.push_back((int)midifile1[track][i][1]);
      cont1++;
   }
   
   cout<<distancia(vect1,vect2)<<" "<<distancia(vect1t,vect2t)-(abs(cont-cont1))<<" "<<cont<<" "<<cont1;

   return 0;
}

void checkOptions(Options& opts) {
   
}


