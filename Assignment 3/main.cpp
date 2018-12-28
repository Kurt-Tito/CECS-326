#include <cstdlib>
#include <unistd.h>
#include <iostream>

//#include <cstring>
//#include <string>

#include <sys/types.h>
#include <sys/wait.h>

//#include <boost/algorithm/string.hpp>

using namespace std;

int main()
{   
    bool exit = false;

    while(!exit)
    {
        //string originalText = "The quick brown fox jumped over the brown lazy dog";
        
        string originalText = "In summer of 1978 he took his first academic position at the University of Nebraska where he remained for 3 years and where he wrote the grants to obtain the Buros Institute for the University, and became the first Director of the Buros Institute after its founder, Oscar Krisen Buros (Reynolds was Acting Director during the search for a permanent new director in 1979–1980 and worked as Associate Director in 1980-1981) prior to being driven south to Texas A&M University (TAMU) by the bitter Nebraska winters. In 2006, he was named the Buros Institute Distinguished Reviewer of the Year. Reynolds taught courses primarily in the areas of psychological testing and diagnosis and in neuropsychology in addition to supervising clinical practica in testing and assessment. He remained at TAMU from summer of 1981, where he was a Professor of Educational Psychology, a Professor of Neuroscience, and a Distinguished Research Scholar, until his retirement from the university on July 31, 2008. In September 2008, he was honored by the Texas A&M University Board of Regents with the title of Emeritus. He currently practices forensic neuroscience in Austin Texas and continues to work in test development.";

        string targetString = "";
        string replacementString = "";

        cout << "Original Text: " << originalText << endl;
        cout << "Choose a word to replace..." << endl;
        cin >> targetString;

        cout << "Enter a word to replace it with... " << endl;
        cin >> replacementString;
        
        long childPID;
        childPID = fork();

        //int count = 0;

        if (childPID < 0)
        {
            cout << "ERROR on fork." << endl;
        }
        else if (childPID == 0)
        {   
            int count = 0;
            int targetPos = originalText.find(targetString);
            //cout << "String found at this location: " << targetPos << endl;
    
            //Loop until it no more matches found
            while (targetPos != -1)
            {
                count++;
                originalText.replace(targetPos, targetString.length(), replacementString);
                targetPos = originalText.find(targetString, targetPos + targetString.length());
            }

            //boost::replace_all(originalText, targetString, replacementString);
            
            if (count == 0)
            {   
                //Injected Bug
                for (;;)
                {
                    cout << ".";
                }
            }
            else
            {
                cout << "New Text: " << originalText << endl;
                cout << "Matches found: " << count << endl;
            }

        }
        else if (childPID > 0)
        {
            wait(0);
        }
        
        string confirm = "";
        cout << "Enter 'yes' to run program again or '!wq' to exit" << endl;
        cin >> confirm;
        
        if (confirm == "!wq")
            exit = true;
        else
            exit = false;
    }

    return 0;
}


void doChildTask()
{
    
}
