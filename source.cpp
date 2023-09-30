#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <fstream>
#include <sstream>
#include <ctime> //for random numbers
//to pause the the screen
#include <chrono>
#include <thread>

#include "linked_list.h"
using namespace std;

// class
class rule
{
public:
    void get_file_data(string**, string**);
    void stringToArray(string str, string* arr, int* j); // suportive function for get file data function
};

class amphire
{
public:
    bool toss();
    int ball_state();
    bool say_out(bool l);
};

class player
{
private:
    string name;
    int runs;

public:
    void add_player(string Name);
    string get_name();
};

class batsman : public player
{
private:
    amphire* Amphire;
    int skill;
    int runs = 0;
    int six=0;
    int four=0;
    int ball = 0;

public:
    void add_batsman(string Name);
    int hit_ball();
    string get_name();
    int get_player_runs();
    int get_no_4();
    int get_no_6();
    void update_skill(int Skill);
};

class bowler : public player, virtual public batsman
{
private:
    amphire* Amphire;
    int probability_get_wicket = 25;
    int wickets_taken = 0;

public:
    int bawling();
    void add_bowler(string Name);
    void got_wicket();
    string get_name();
    bool get_wicket();
    int print_wicket_taken();
 
};

class all_rounder : virtual public batsman, virtual public bowler
{
private:
    amphire* Amphire;

public:
    void add_all_rounder(string Name);
    string get_name();
};

class team
{
private:
    batsman* p_batsman = nullptr;
    bowler* p_bowler = nullptr;
    all_rounder* p_all_rounder = nullptr;
    amphire* Amphire;
    string name;
    int no_batsman;
    int no_bowlers;
    int no_all_rounders;
    int wickets = 0;
    int rem_balls;
    int runs =0;
    string line; // store batsmans runs
    string current_bowler;  //store current bowler name

    // linked list to store not out players in batting team
    LinkList bat;
    LinkList ball;
    LinkList all;

public:
    void add_team(string** team_array);
    void add_players(string** team_array);
    bool select_bat_bowl();
    void initiate_balls(int Rem_balls);
    bool bowlling_condition(team* teambat);
    int pass_ball(int team_ball, int* current_bowler_index, int* player_type);
    void update_balls(int ball_type);
    void print_batsman_details();
    void print_bowler_details();
    void print_all_rounders_details();
    string get_current_bowler();
    int get_no_of_wickects();
    int get_team_runs();
    string get_team_name();
    string get_batsman_current_runs();
    void update_wickets();
    void update_runs(int Run);
    void not_out_players();
    void batting(int a);
    int get_rem();
};

class game : protected amphire, protected rule
{
private:
    team team1;
    team team2;
    bool is_team1 = 1;
    bool first_bat;
    bool toss_winner;
    int overs = 20;
    int current_bowler_index, player_type; // 0-bowler ,1-all rounder, both variables use together

    // array to sore team data while reading
    string** team1_array = new string * [11];
    string** team2_array = new string * [11];

public:
    game();
    void get_team_data();
    bool start_toss();
    bool is_firstbat();
    void start_match();  
    void playing(team* Teambat, team* Teamball, int balling_team_no);
    void chasing_score();   
    void playing_chase(team* Teambat, team* Teamball, int balling_team_no); 
    void print_final_score(team Teambat, team Teamball, int balling_team_no, int match_win_team);  
    void summery(team Team);
 
};

int main()
{
    int selection;
    // for generate random number
    srand(static_cast<unsigned int>(time(nullptr)));

    //create game object
    game Game;

    cout << "\n------------------------------------------------------------" << endl;
    cout << "\t\t  CRICKET GAME" << endl;
    cout << "------------------------------------------------------------\n" << endl;

    cout << ":-: START NEW GAME " << endl;
    cout << "---------------------------\n" << endl;
    cout << "Do you need to start a new cricket game ?\n\t1 - yes\n\t0 - EXIT \n\nEnter selection : ";
    cin >> selection;

    if (selection == 1)
    {
        system("cls");
        cout << "\n---------------------------" << endl;
        cout << "Take the toss : " << endl;
        cout << "---------------------------" << endl;
        // After toss
        Game.start_toss();

        //select first bat team
        if (Game.is_firstbat())
            cout << "     ::They decided to bowlling first " << endl;
        else
            cout << "     ::They decided to batting first " << endl;

        cout << "---------------------------" << endl;
        cout << "\nMatch is going to start..." << endl;
        this_thread::sleep_for(chrono::milliseconds(3000));  //screen pause for 3 seconds
    }
    else if (selection == 0)
    {
        cout << "EXIT" << endl;
        return 0;
    }
    else
    {
        system("cls");
        cout << "   INPUT DISMATCH  ! TRY AGAIN " << endl;
        main();
    }

      system("cls");

     // start match
    Game.start_match();
        
    cout << "\nBreak" << endl;
    cout << "Match will start in few seconds..." << endl;
    this_thread::sleep_for(chrono::milliseconds(5000));  //screen pause for 2 seconds
    system("cls");

    //second team bat
    Game.chasing_score();

    cout << "\nPress ENTER to return the MAIN Menu : " << endl;
    system("pause");
    system("cls");
    
    return 0;
}

// Function declerations of classes
//_________________________________________________________________________________

// Rule class----------------
void rule::stringToArray(string str, string* arr, int* j)
{
    istringstream iss(str);
    string word;
    int i = 0;
    while (iss >> word)
    {
        arr[i] = word;
        i++;
    }
    *j = i;
}

void rule::get_file_data(string** team1_array, string** team2_array)
{
    // declare variables
    ifstream file;   // file object to read file
    string fileline; // to hold a line of text from the file
    int size = 11;
    int words = 0; // No of words in a string
    int num = 0;
    int selection = 0;  // to select appropriate dynamic memory to store team details
    string* arr = NULL; // to hold words of string temperory after split

    // open the file
    file.open("data.txt", ios::in); // file name and file stream type

    // read the file line by line
    while (getline(file, fileline))
    {
        if ((fileline == "********************") || (fileline == "--------------------"))
            continue;
        else if (fileline == "   TEAM 1 DETAILS")
            selection = 1;
        else if (fileline == "   TEAM 1 PLAYERS")
        {
            selection = 2;
        }
        else if (fileline == "   TEAM 2 DETAILS")
            selection = 3;
        else if (fileline == "   TEAM 2 PLAYERS")
        {
            selection = 4;
            num = 0;
        }
        else if (selection == 1)
        {
            arr = new string[size];
            stringToArray(fileline, arr, &words);

            if (arr[0] == "Name")
            {
                int j = 1;
                while (j != words + 1)
                {
                    team1_array[0][0] = team1_array[0][0] + arr[j] + " ";
                    j++;
                }
            }
            else if (arr[0] == "Batsmans")
            {
                team1_array[0][1] = arr[1];
            }
            else if (arr[0] == "Bowlers")
            {
                team1_array[0][2] = arr[1];
            }
            else if (arr[0] == "All_rounders")
            {
                team1_array[0][3] = arr[1];
            }
            delete[] arr;
        }
        else if (selection == 2)
        {
            if (num < 11) //  don't access out-of-bounds of the array
            {
                team1_array[1][num] = fileline;
                num++;
            }
        }
        else if (selection == 3)
        {
            arr = new string[size];
            stringToArray(fileline, arr, &words);

            if (arr[0] == "Name")
            {
                int j = 1;
                while (j != words + 1)
                {
                    team2_array[0][0] = team2_array[0][0] + arr[j] + " ";
                    j++;
                }
            }
            else if (arr[0] == "Batsmans")
            {
                team2_array[0][1] = arr[1];
            }
            else if (arr[0] == "Bowlers")
            {
                team2_array[0][2] = arr[1];
            }
            else if (arr[0] == "All_rounders")
            {
                team2_array[0][3] = arr[1];
            }
            delete[] arr;
        }
        else if (selection == 4)
        {
            if (num < 11) //  don't access out-of-bounds of the array
            {
                team2_array[1][num] = fileline;
                num++;
            }
        }
    }
}

//Player class_______________
void player::add_player(string Name)
{
    name = Name;
}

//Amphire class______________
bool amphire::toss()
{
    return rand() % 2;
}

int amphire::ball_state()
{
    int ran_num = rand() % 100;
    if (ran_num > 90)
        return 1;
    else if (ran_num > 90)
        return 2;
    else
        return 0;
}

bool amphire::say_out(bool l)
{
    // there is only 0.5 probability to be true  that result
    if ((rand() % 100 > 50) && l)
        return true; // pass out
    else
        false; // pass not out
}

string player::get_name()
{
    return name;
}

//Game class-----------------
game::game()
{
    get_team_data();
    team1.add_team(team1_array);
    team2.add_team(team2_array);
}

void game::get_team_data()
{
    for (int i = 0; i < 11; i++)
    {
        team1_array[i] = new std::string[11];
        team2_array[i] = new std::string[11];
    }
    // call function to extract data from file
    get_file_data(team1_array, team2_array);

    /*
        //___________________________________________
        //delete dynamic memory allocation
        for (int i = 0; i < 11; i++)
        {
            delete[] team1_array[i];
            delete[] team2_array[i];
        }
        delete[] team1_array;
        delete[] team2_array;*/
}

bool game:: start_toss()
{
    // load players to array
    team1.not_out_players();
    team2.not_out_players();

    toss_winner = toss();
    cout << "     ::Toss won by       :  Team " << (toss_winner == 0 ? team1.get_team_name() : team2.get_team_name()) << endl;
    return toss_winner;
}

bool game:: is_firstbat()
{
    if (toss_winner = 0) // team1 won the toss
        first_bat = team1.select_bat_bowl();
    else
        first_bat = team2.select_bat_bowl();

    return first_bat; // 0 batting , 1 bawling
}

void game::start_match()
{
    team1.initiate_balls(6 * overs);
    team2.initiate_balls(6 * overs);

    if (((toss_winner == 0) && (first_bat == 0)) || ((toss_winner == 1) && (first_bat == 1))) // Team 1 is going to batting first
    {
        playing(&team1, &team2, 2);
    }
    else if (((toss_winner == 1) && (first_bat == 0)) || ((toss_winner == 0) && (first_bat == 1))) // Team 2 is going to batting first
    {
        playing(&team2, &team1, 1);
    }
}

void game::playing(team* Teambat, team* Teamball, int balling_team_no)
{
    int temp;
    do
    {
        system("cls");
        cout << "\n------------------------------------------------------------" << endl;
        cout << "\t\t  Live Cricket Score" << endl;
        cout << "------------------------------------------------------------\n" << endl;
        cout << setw(30) << "LIVE\n" << endl;

        // cout << "__________________________________" << endl;
        cout << (*Teambat).get_team_name() << setw(10);
        cout << (*Teambat).get_team_runs() << " / " << (*Teambat).get_no_of_wickects() << setw(35) << (*Teamball).get_team_name() << endl;
        cout << right << setfill(' ') << setw(17) << "(" << int((6 * overs - (*Teamball).get_rem()) / 6) << "." << (6 * overs - (*Teamball).get_rem()) % 6 << ")" << setw(40) << "(yet to bat)" << endl;

        cout << "\n" << endl;
        cout << setw(38);

        // pass ball by bowling team
        temp = (*Teamball).pass_ball(balling_team_no, &current_bowler_index, &player_type);

        // Batting team hit to the ball
        if (temp == 0) // normal ball batsman can hit
        {
            (*Teambat).batting(balling_team_no);
        }
        else if (temp == -2)
            (*Teambat).update_wickets();
         else if (temp == 2) // wide ball ,runs++;
            (*Teambat).update_runs(1);
         else if (temp == 1) // no ball ,runs++;
            (*Teambat).update_runs(1);

        cout << "____________________________________________________________" << endl;
        cout << "------------------------------------------------------------\n" << endl;
        cout << (*Teambat).get_team_name() << " batting " << setw(36) << (*Teamball).get_team_name() << " bowlling" << endl;
        //cout << "-------------------"<<setw(42)<<"-------------------" << endl;
        cout << " ::" << (*Teambat).get_batsman_current_runs() << "* " << right << setfill(' ') << setw(23) << " ::" << (*Teamball).get_current_bowler() << " (" << ((6 * overs - (*Teamball).get_rem()) % 6) + 1 << ")" << endl;

        this_thread::sleep_for(chrono::milliseconds(1000));  //screen pause for 1 seconds


    } while ((*Teamball).bowlling_condition(Teambat));
}

void game:: chasing_score()
{
    if (((toss_winner == 0) && (first_bat == 0)) || ((toss_winner == 1) && (first_bat == 1))) // Team 2 is going to chase score
    {
        playing_chase(&team2, &team1, 1);
    }
    else if (((toss_winner == 1) && (first_bat == 0)) || ((toss_winner == 0) && (first_bat == 1))) // Team 1 is going to chase score
    {
        playing_chase(&team1, &team2, 2);
    }
}

void game:: playing_chase(team* Teambat, team* Teamball, int balling_team_no)
{
    int temp, runs_needed;
    do
    {
        cout << "\n------------------------------------------------------------" << endl;
        cout << "\t\t  Live Cricket Score" << endl;
        cout << "------------------------------------------------------------\n" << endl;
        cout << setw(30) << "LIVE\n" << endl;

        // cout << "__________________________________" << endl;
        cout << (*Teamball).get_team_name() << setw(10);
        cout << (*Teamball).get_team_runs() << " / " << (*Teamball).get_no_of_wickects() << setw(35) << (*Teambat).get_team_name() << (*Teambat).get_team_runs() << " / " << (*Teambat).get_no_of_wickects() << endl;
        cout << setw(14) << "(" << int((6 * overs - (*Teambat).get_rem()) / 6) << "." << (6 * overs - (*Teambat).get_rem()) % 6 << ")" << setw(40) << "(" << int((6 * overs - (*Teamball).get_rem()) / 6) << "." << (6 * overs - (*Teamball).get_rem()) % 6 << ")" << endl;

        cout << "\n" << endl;
        cout << setw(38);

        // pass ball by bowling team
        temp = (*Teamball).pass_ball(balling_team_no, &current_bowler_index, &player_type);

        // Batting team hit to the ball
        if (temp == 0) // normal ball batsman can hit
        {
            (*Teambat).batting(balling_team_no);
        }
        else if (temp == -2)
            (*Teambat).update_wickets();
        else if (temp == 2) // wide ball ,runs++;
            (*Teambat).update_runs(1);
        else if (temp == 1) // no ball ,runs++;
            (*Teambat).update_runs(1);

        runs_needed = (Teamball->get_team_runs() - Teambat->get_team_runs());
        cout << setw(20) << (*Teambat).get_team_name() << " needs " << runs_needed << " runs to win." << endl;
      
        cout << "____________________________________________________________" << endl;
        cout << "------------------------------------------------------------\n" << endl;
        cout << (*Teambat).get_team_name() << " batting " << setw(36) << (*Teamball).get_team_name() << " bowlling" << endl;
       
        cout << " ::" << (*Teambat).get_batsman_current_runs() << "* " << right << setfill(' ') << setw(23) << " ::" << (*Teamball).get_current_bowler() << " (" << ((6 * overs - (*Teamball).get_rem()) % 6) + 1 << ")" << endl;

        if ((runs_needed == 0) && (Teamball->get_no_of_wickects() == 10 || Teambat->get_rem() == 0))
        {
            print_final_score(*Teambat, *Teamball, balling_team_no, -1);
        }
        else if (runs_needed < 0)
        {
            if (balling_team_no == 1)
                print_final_score(*Teambat, *Teamball, balling_team_no, 2);
            else
                print_final_score(*Teambat, *Teamball, balling_team_no, 1);
            break;
        }
        else if ((*Teamball).bowlling_condition(Teambat) == 0)
            print_final_score(*Teambat, *Teamball, balling_team_no, balling_team_no);

        this_thread::sleep_for(chrono::milliseconds(1000));  //screen pause for 1 seconds
       
        system("cls");
    } while ((*Teamball).bowlling_condition(Teambat));
}

void game:: print_final_score(team Teambat, team Teamball, int balling_team_no, int match_win_team)
{
    system("cls");
    int temp, runs_needed;

    cout << "\n------------------------------------------------------------" << endl;
    cout << "\t\t  Live Cricket Score" << endl;
    cout << "------------------------------------------------------------\n" << endl;
    cout << setw(30) << "LIVE\n" << endl;

    // cout << "__________________________________" << endl;
    cout << (Teamball).get_team_name() << setw(10);
    cout << (Teamball).get_team_runs() << " / " << (Teamball).get_no_of_wickects() << setw(35) << (Teambat).get_team_name() << (Teambat).get_team_runs() << " / " << (Teambat).get_no_of_wickects() << endl;
    cout << setw(14) << "(" << int((6 * overs - (Teambat).get_rem()) / 6) << "." << (6 * overs - (Teambat).get_rem()) % 6 << ")" << setw(40) << "(" << int((6 * overs - (Teamball).get_rem()) / 6) << "." << (6 * overs - (Teamball).get_rem()) % 6 << ")" << endl;

    cout << "\n" << endl;
    cout << "____________________________________________________________" << endl;
    cout << "------------------------------------------------------------\n" << endl;
    cout << setw(38);
    if (match_win_team == -1)
    {
        cout << setw(20) << " Match Draw " << endl;
    }
    else if (match_win_team == balling_team_no)
    {
        runs_needed = (Teamball.get_team_runs() - Teambat.get_team_runs());
        cout << setw(20) << (Teamball).get_team_name() << " won by " << runs_needed << " runs ." << endl;
    }
    else
    {
        runs_needed = (Teambat.get_team_runs() - Teamball.get_team_runs());
        cout << setw(20) << (Teambat).get_team_name() << " won by " << 10 - Teambat.get_no_of_wickects() << " wickets ." << endl;
    }

    cout << "------------------------------------------------------------" << endl;
    cout << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;

    this_thread::sleep_for(chrono::milliseconds(2000));  //screen pause for 2 seconds
    summery(team1);
    summery(team2);
    system("pause");
    //system("cls");
}

void game:: summery(team Team)
{
    cout << "\n.............................................................." << endl;
    cout << "SCORECARD" << endl;
    cout << "..............................................................\n" << endl;
    cout << "*************" << Team.get_team_name() << "*************" << endl;

    cout << "\nBatsmen\n_____________" << endl;
    cout << setw(40) << "4s" << setw(10) << "6s" << setw(10) << "Runs" << endl;
    Team.print_batsman_details();
    cout << "\nAll rounders\n_____________" << endl;
    cout << setw(40) << "4s" << setw(10) << "6s" << setw(10) << "Runs" << setw(10) << "Wickets" << endl;
    Team.print_all_rounders_details();
    cout << "\nBowlers\n_____________" << endl;
    cout << setw(40) << "4s" << setw(10) << "6s" << setw(10) << "Runs" << setw(10) << "Wickets" << endl;
    Team.print_bowler_details();
}

// Team class----------------
void team::add_team( string** team_array)
{
    name = team_array[0][0];
    add_players(team_array);
}

void team::add_players(string** team_array)
{
    no_batsman = stoi(team_array[0][1]);
    no_bowlers = stoi(team_array[0][2]);
    no_all_rounders = stoi(team_array[0][3]);

    int k = stoi(team_array[0][1]);
    int j = stoi(team_array[0][2]) + stoi(team_array[0][1]);
    p_batsman = new batsman[no_batsman];
    p_bowler = new bowler[no_bowlers];
    p_all_rounder = new all_rounder[no_all_rounders];

    for (int i = 0; i < stoi(team_array[0][1]); i++)
    {
        p_batsman[i].add_batsman(team_array[1][i]); // add batsmans
    }
    for (int i = 0; i < stoi(team_array[0][2]); i++)
    {
        p_bowler[i].add_bowler(team_array[1][(i + k)]); // add bowlers
    }
    for (int i = 0; i < stoi(team_array[0][3]); i++)
    {
        p_all_rounder[i].add_all_rounder(team_array[1][(i + j)]); // add all rounder
    }
}

bool team::select_bat_bowl()
{
    int r = rand() % 100;
    if (r > 70)
        return 0; // first bat
    else
        return 1; // first bawling
}

void team::initiate_balls(int Rem_balls)
{
    rem_balls = Rem_balls;
}

bool team::bowlling_condition(team *teambat)
{
    return ((teambat->get_no_of_wickects() < 10) && (rem_balls != 0));
}

int team::pass_ball(int team_ball, int* current_bowler_index, int* player_type)
{
    int ball_status;
    int index = 0;
    int temp1, temp2, ran;
    ran = rand(); // get random no
    int temp;

    if (rem_balls % 6 == 0)
    {
        temp = ran % 2;

        // select randomly all rounder or bowler to bowlling
        if (temp == 0)
        {
            index = ran % no_bowlers;
            current_bowler = p_bowler[index].get_name();
            update_balls(ball_status = p_bowler[index].bawling());

            // Try to get wicket
            if ((Amphire->say_out(p_bowler[index].get_wicket()) == 1) && ball_status ==0 )
            {
                p_bowler[index].got_wicket();
                cout << "Pass ball :> OUT " << endl;
                return -2;
            }
        }
        else
        {
            index = ran % no_all_rounders;
            current_bowler = p_bowler[index].get_name();
            update_balls(ball_status = p_all_rounder[index].bawling());

            // Try to get wicket
            if ((Amphire->say_out(p_all_rounder[index].get_wicket()) == 1) && ball_status == 0 )
            {
                p_all_rounder[index].got_wicket();
                cout << "Pass ball :> OUT " << endl;
                return -2;
            }
        }
        player_type = &temp;
        current_bowler_index = &index;
    }
    else
    {
        int index = (*current_bowler_index);
        if (*player_type == 0)
        {
            update_balls(ball_status = p_bowler[index].bawling());

            // Try to get wicket
            if ((Amphire->say_out(p_bowler[index].get_wicket()) == 1) && ball_status == 0 )
            {
                p_bowler[index].got_wicket();
                cout << "Pass ball :> OUT " << endl;
                return -2;
            }
        }
        else
        {
            update_balls(ball_status = p_all_rounder[index].bawling());

            // Try to get wicket
            if ((Amphire->say_out(p_all_rounder[index].get_wicket()) == 1) && ball_status == 0 )
            {
                p_all_rounder[index].got_wicket();
                cout << "Pass ball :> OUT " << endl;
                return -2;
            }
        }
    }
    return ball_status;
}

void team::update_balls(int ball_type)
{
    if (ball_type == 0)
        rem_balls--;
    else if (ball_type == 2)
    {
        rem_balls--;
        runs++;
    }
}

void team::print_batsman_details()
{
    for (int i = 0;i < no_batsman;i++)
    {
        cout << left << setfill(' ') << setw(20) << p_batsman[i].get_name() << setw(20) << right << setfill(' ') << setw(20) << p_batsman[i].get_no_4() << setw(10) << p_batsman[i].get_no_6() << setw(10) << p_batsman[i].get_player_runs() << endl;
    }
}

void team::print_bowler_details()
{
    for (int i = 0;i < no_bowlers;i++)
    {
        cout << left << setfill(' ') << setw(20) << p_bowler[i].get_name() << setw(20)<<right << setfill(' ') << setw(20) << p_bowler[i].get_no_4() << setw(10) << p_bowler[i].get_no_6() << setw(10) << p_bowler[i].get_player_runs() << setw(10) << p_bowler[i].print_wicket_taken() << endl;
    }
}

void team::print_all_rounders_details()
{
    for (int i = 0;i < no_all_rounders;i++)
    {
        cout <<left<<setfill(' ') << setw(20) << p_all_rounder[i].get_name() << setw(20) <<right<<setfill(' ')<<setw(20)<< p_all_rounder[i].get_no_4() << setw(10) << p_all_rounder[i].get_no_6() << setw(10) << p_all_rounder[i].get_player_runs() << setw(10) << p_all_rounder[i].print_wicket_taken() << endl;
    }
}

string team::get_current_bowler()
{
    return current_bowler;
}

int team::get_no_of_wickects()
{
    return wickets;
}

int team::get_team_runs()
{
    return runs;
}

string team::get_team_name()
{
    return this->name;
}

string team::get_batsman_current_runs()
{
    return line;
}

void team::update_wickets()
{
    wickets++;
    if (wickets <= no_batsman)
        bat.deleteBeg();
    else if (wickets <= (no_batsman + no_all_rounders))
        all.deleteBeg();
    else if (wickets < 11)
        ball.deleteBeg();
}

void team::update_runs(int Run)
{
    runs = runs + Run;
}

void team::not_out_players()
{
    bat.add(no_batsman);
    ball.add(no_bowlers);
    all.add(no_all_rounders);
}

void team::batting(int a)
{
    line = " ";
    int temp_score;
    if (wickets == 0 && bat.printfirstelement() != -1)
    {
        temp_score = p_batsman[bat.printfirstelement()].hit_ball();
        runs += temp_score;
       
        line = p_batsman[bat.printfirstelement()].get_name() + " : " + to_string(p_batsman[bat.printfirstelement()].get_player_runs());
    }
    else if (wickets < 11 && bat.printfirstelement() != -1)
    {
        temp_score = p_batsman[bat.printfirstelement()].hit_ball();
        runs += temp_score;
       
        line = p_batsman[bat.printfirstelement()].get_name() + " : " + to_string(p_batsman[bat.printfirstelement()].get_player_runs());
    }
    else if ((bat.printfirstelement() == -1) && (all.printfirstelement() != -1) && (wickets < 11))
    {
        temp_score = p_all_rounder[all.printfirstelement()].hit_ball();
        runs += temp_score;
        line = p_all_rounder[all.printfirstelement()].get_name() + " : " + to_string(p_all_rounder[all.printfirstelement()].get_player_runs());
    }
    else if ((bat.printfirstelement() == -1) && (all.printfirstelement() == -1) && (wickets < 11))
    {
        temp_score = p_bowler[ball.printfirstelement()].hit_ball();
        runs += temp_score;
        line = p_bowler[ball.printfirstelement()].get_name() + " : " + to_string(p_bowler[ball.printfirstelement()].get_player_runs());
    }
}

int team::get_rem()
{
    return rem_balls; 
}

// Bowler class______________
int bowler::bawling()
{
    int temp = Amphire->ball_state();
    if (temp == 0) // normal ball
    {
        return 0;
    }
    else if (temp == 1) // no ball
    {
        cout << "Pass ball :> No ball : " << endl;
        return 1;
    }
    else if (temp == 2) // wide ball
    {
        cout << "Pass ball :> Wide ball : " << endl;
        return 2;
    }
}

void bowler::add_bowler(string Name)
{
    player::add_player(Name);
    update_skill(40);
}

void bowler::got_wicket()
{
    wickets_taken++;
}

string bowler::get_name()
{
    return player::get_name();
}

bool bowler::get_wicket()
{
    int random = rand() % 100;
    if (random < probability_get_wicket)
        return 1; // wicket is pending, wait for amphire's decision
    else
        return 0; // not get
}

int bowler::print_wicket_taken()
{
    return wickets_taken;
}

// Batsman class______________
int batsman::hit_ball()
{
    ball++;
    int num = rand() % 100;
    if (skill > 50)
    {
        if (num > 85)
        {
            cout << "Pass ball :> 1 runs " << endl;
            batsman::runs++;
            return 1;
        }
        else if (num > 75)
        {
            cout << "Pass ball :> 2 runs " << endl;
            batsman::runs += 2;
            return 2;
        }
        else if (num > 55)
        {
            cout << "Pass ball :> 3 runs " << endl;
            batsman::runs += 3;
            return 3;
        }
        else if (num > 20)
        {
            cout << "Pass ball :> 4 runs " << endl;
            batsman::runs += 4;
            batsman::four++;
            return 4;
        }
        else if (num > 5)
        {
            cout << "Pass ball :> 6 runs " << endl;
            batsman::runs = runs+ 6;
            batsman::six++;
            return 6;
        }
        else
        {
            cout << "Pass ball :> 7 runs " << endl;
            batsman::runs += 7;
            batsman::six++;
            return 7;
        }
    }
    else
    {
        if (num > 65)
        {
            cout << "Pass ball :> 1 runs " << endl;
            batsman::runs++;
            return 1;
        }
        else if (num > 35)
        {
            cout << "Pass ball :> 2 runs " << endl;
            batsman::runs += 2;
            return 2;
        }
        else if (num > 25)
        {
            cout << "Pass ball :> 3 runs " << endl;
            batsman::runs += 3;
            return 3;
        }
        else if (num > 15)
        {
            cout << "Pass ball :> 4 runs " << endl;
            batsman::runs += 4;
            batsman::four++;
            return 4;
        }
        else if(num > 5)
        {
            cout << "Pass ball :> 6 runs " << endl;
            batsman::runs += 6;
            batsman::six++;
            return 6;
        }
        else
        {
            cout << "Pass ball :> 7 runs " << endl;
            batsman::runs += 7;
            batsman::six++;
            return 7;
        }
    }
}

void batsman::update_skill(int Skill)
{
    batsman::skill = Skill;
}

void batsman::add_batsman(string Name)
{
    batsman::skill = 80;
    player::add_player(Name);
}

string batsman::get_name()
{
    return player::get_name();
}

int batsman::get_player_runs()
{
    return runs;
}

int batsman::get_no_4()
{
    return four;
}

int batsman::get_no_6()
{
    return six;
}

// All Rounder class__________
void all_rounder::add_all_rounder(string Name)
{
    player::add_player(Name);
    update_skill(60);
}

string all_rounder:: get_name()
{
    return player::get_name();
}