#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

#include "utils.h"

// include build configuration defines
#include "../config.h"

vector<string> namesA = {"Johnson", "Adams", "Davis", "Simons", "Richards", "Taylor", "Carter", "Stevenson", "Taylor", "Smith", "McDonald", "Harris", "Sim", "Williams", "Baker", "Wells", "Fraser", "Jones", "Wilks", "Hunt", "Sanders", "Parsons", "Robson", "Harker"};
vector<string> namesB = {"Jonson", "Addams", "Davies", "Simmons", "Richardson", "Tailor", "Chater", "Stephenson", "Naylor", "Smythe", "MacDonald", "Harrys", "Sym", "Wilson", "Barker", "Wills", "Frazer", "Johns", "Wilkinson", "Hunter", "Saunders", "Pearson", "Robertson", "Parker"};

void
string_to_soundex(string& name, string& sndex)
{
  int si = 1;
  int c;

  //                 ABCDEFGHIJKLMNOPQRSTUVWXYZ
  char mappings[] = "01230120022455012623010202";

  sndex.clear();
  sndex += toupper(name[0]);

  for (unsigned i = 1, len = name.size(); i < len; i++)
  {
    c = (int)toupper(name[i]) - 65;

    if (c >= 0 && c <= 25)
    {
      if (mappings[c] != '0')
      {
        if (mappings[c] != sndex[si-1])
        {
          sndex += mappings[c];
          si++;
        }

        if (si > 3)
          break;
      }
    }
  }

  if (si <= 3)
  {
    while(si <= 3)
    {
      sndex += '0';
      si++;
    }
  }
}


int
main(void)
{
  // initialize the privacy enhanced execution target
  VIP_INIT;

  vector<string> sndexA(namesA.size());
  vector<string> sndexB(namesB.size());

  {
    Stopwatch s("VIP_Bench Runtime");
    for (unsigned i = 0; i < sndexA.size(); i++)
    {
      string_to_soundex(namesA[i], sndexA[i]);
      string_to_soundex(namesB[i], sndexB[i]);
    }
  }

  // print the results
  unsigned trial;
  for (trial=0; trial < sndexA.size(); trial++)
  {
    const char *res = sndexA[trial].compare(sndexB[trial]) == 0 ? "true" : "false";
    fprintf(stdout, "trial %3u: %-20s[%-6s] =? %-20s[%-6s] --> %s\n",
            trial, namesA[trial].c_str(), sndexA[trial].c_str(), namesB[trial].c_str(), sndexB[trial].c_str(), res);
  }

  fprintf(stderr, "INFO: %u trials performed.\n", trial);
  return 0;
}


#ifdef notdef
void main(void)
{
    puts("-----------------");
    puts("| codedrome.com |");
    puts("| Soundex       |");
    puts("-----------------\n");

    char* names1[] = {"Johnson", "Adams", "Davis", "Simons", "Richards", "Taylor", "Carter", "Stevenson", "Taylor", "Smith", "McDonald", "Harris", "Sim", "Williams", "Baker", "Wells", "Fraser", "Jones", "Wilks", "Hunt", "Sanders", "Parsons", "Robson", "Harker"};

    char* names2[] = {"Jonson", "Addams", "Davies", "Simmons", "Richardson", "Tailor", "Chater", "Stephenson", "Naylor", "Smythe", "MacDonald", "Harrys", "Sym", "Wilson", "Barker", "Wills", "Frazer", "Johns", "Wilkinson", "Hunter", "Saunders", "Pearson", "Robertson", "Parker"};

    int namecount = sizeof(names1) / sizeof(names1[0]);

    char s1[] = "     ";
    char s2[] = "     ";

    for(int i = 0; i < namecount; i++)
    {
        soundex(names1[i], s1);
        soundex(names2[i], s2);

        printf("%-20s%-6s%-20s%-6s\n", names1[i], s1, names2[i], s2);
    }
}
#endif
