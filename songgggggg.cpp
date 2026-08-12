#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

using namespace std;


/* =========================================================
                    🔴 AUDIO FILE LOCATION
   =========================================================

   CHANGE ONLY THIS LINE.

   Example:

   const string AUDIO_FILE =
       R"(C:\Users\NSSD1\OneDrive\Desktop\Songs\Falak.mp3)";
*/

const string AUDIO_FILE =
    R"(Falak.mp3.mpeg)";


/* =========================================================
                    LYRIC STRUCTURE
   ========================================================= */

struct Line
{
    string text;

    // Time in milliseconds from beginning of song
    int startTime;

    // Windows console color
    int color;
};


/* =========================================================
                    SONG LYRICS
   =========================================================

   1000 ms = 1 second

   Change ONLY the startTime values if you
   need to synchronize the lyrics more accurately.
*/

vector<Line> lyrics =
{
   { "............",
    0,   
    8
    },

    // Line 1
    {
        "Falak Se Puch Lo Chahe",
        1350,
        11
    },

    // Line 2
    {
        "Gawah Ye Chaand Taare Hai",
        4750,
        10
    },

    // Line 3
    {
        "Na Samjho Ajnabi Sadiyon Se",
        8000,
        13
    },

    // Line 4
    {
        "Hum To Bass Tumhare Hai",
        11400,
        12
    },
   
    // Line 5
    {
        "Mohabbat Se Nahi Waakif",
        15500,
        14
    },

    // Line 6
    {
        "Bahut Anjaan Lagti Ho",
        18400,
        9
    },

    // Line 7
    {
        "Humein Milna Zaroori Hai",
        21400,
        10
    },

    // Line 8
    {
        "Haqiqat Na Samajhti Ho",
        24600,
        13
    }
};


/* =========================================================
                    CLEAR SCREEN
   ========================================================= */

void clearScreen()
{
    system("cls");
}


/* =========================================================
                    SET COLOR
   =========================================================

   Windows console colors:

   9  = Light Blue
   10 = Light Green
   11 = Light Cyan
   12 = Light Red
   13 = Light Magenta
   14 = Yellow
*/

void setColor(int color)
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        color
    );
}


/* =========================================================
                    RESET COLOR
   ========================================================= */

void resetColor()
{
    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        7
    );
}


/* =========================================================
                    OPEN AUDIO
   ========================================================= */

bool openAudio()
{
    string command =
        "open \"" +
        AUDIO_FILE +
        "\" type mpegvideo alias song";

    MCIERROR error =
        mciSendStringA(
            command.c_str(),
            NULL,
            0,
            NULL
        );

    return error == 0;
}


/* =========================================================
                    PLAY AUDIO
   ========================================================= */

void playAudio()
{
    mciSendStringA(
        "play song",
        NULL,
        0,
        NULL
    );
}


/* =========================================================
                    STOP AUDIO
   ========================================================= */

void stopAudio()
{
    mciSendStringA(
        "stop song",
        NULL,
        0,
        NULL
    );

    mciSendStringA(
        "close song",
        NULL,
        0,
        NULL
    );
}


/* =========================================================
                DISPLAY CURRENT LINE
   ========================================================= */

void displayLine(int currentLine)
{
    clearScreen();

    cout << "\n\n\n";

    cout << "====================================================\n";

    setColor(15);

    cout << "                 FALAK - LYRICS";

    resetColor();

    cout << "\n";

    cout << "====================================================\n\n\n";


    /*
        Display the current lyric line
        in its assigned color.
    */

    setColor(
        lyrics[currentLine].color
    );


    cout << "             "
         << lyrics[currentLine].text
         << endl;


    resetColor();

    cout << "\n\n";
}


/* =========================================================
                        MAIN
   ========================================================= */

int main()
{
    clearScreen();


    /* -----------------------------------------------------
                    OPEN AUDIO
       ----------------------------------------------------- */

    if (!openAudio())
    {
        setColor(12);

        cout << "\n\n";
        cout << "ERROR: Audio file could not be opened!\n\n";

        resetColor();

        cout << "Check this line:\n\n";

        cout << "const string AUDIO_FILE =\n";

        cout << "R\"(YOUR AUDIO PATH HERE)\";\n\n";

        cout << "Current path:\n";
        cout << AUDIO_FILE << "\n\n";

        system("pause");

        return 1;
    }


    /* -----------------------------------------------------
                    START AUDIO
       ----------------------------------------------------- */

    playAudio();


    /*
        Start timer immediately after
        starting the audio.
    */

    DWORD songStartTime =
        GetTickCount();


    /* -----------------------------------------------------
                    DISPLAY LYRICS
       ----------------------------------------------------- */

    for (int i = 0; i < lyrics.size(); i++)
    {
        /*
            Calculate elapsed time.
        */

        DWORD currentTime =
            GetTickCount() -
            songStartTime;


        /*
            Wait until the correct
            timestamp.
        */

        if (currentTime <
            lyrics[i].startTime)
        {
            Sleep(
                lyrics[i].startTime -
                currentTime
            );
        }


        /*
            Display complete line.
        */

        displayLine(i);
    }


    /* -----------------------------------------------------
                    END OF SONG
       ----------------------------------------------------- */

    Sleep(3000);

    stopAudio();


    /* -----------------------------------------------------
                    END SCREEN
       ----------------------------------------------------- */

    clearScreen();

    setColor(11);

    cout << "\n\n\n";

    cout << "====================================================\n";
    cout << "                    ~ THE END ~\n";
    cout << "====================================================\n";

    resetColor();


    return 0;
}