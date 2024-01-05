#include<iostream>
#include<string>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
#include<limits>
#include<cctype>
#include<algorithm>
using namespace std;
int globalColor; // global variable
struct Hero
{
    string user_name;
    string class_type;
    int health_points;
    int maxHealth;
    int exp_points;
    int level = 1;
    int damage;
    string inventory[10];
    int inventorySize;

};

struct Monster
{
    string name;
    int monsterHealth;
    int monsterDamage;
    int monsterAttack;
};

struct Quest
{
    Hero player;
    Monster monsters;
    bool exitQuest;
    bool lostBattle;
};

void setColor(int colorCode);
void resetColor();
int chooseColor();
void setGameColor();
void displayInstructions();
Hero initializeCharacters();
void display_HeroInformation(Hero& character);
void displayInventory(Hero& character);
void addtoInventory(Hero& character, string& item);
int display_Menu();
int display_questsMenu();
void gainExperience(Hero& character, int xp);
Hero levelUp(Hero& character);



void display_battle1_instructions();
Quest quest_1(Hero& character, Monster& monsters);
Quest battle_quest1(Hero& character, Monster& monsters);


Quest quest2(Hero& character, Monster& monsters);
Quest battle_quest2(Hero& character, Monster& monsters);
Quest bossbattle2(Hero& character, Monster& monsters);


Quest quest3(Hero& character, Monster& monsters);
Quest battle_quest3(Hero& character, Monster& monsters);
Quest bossbattle_3(Hero& character, Monster& monsters);
bool puzzle_3(Hero& character);

int main()
{
    srand(time(0)); // initialize time seed 
    Hero player; // create a player variable with Hero struct dataype
    Monster Monsters;
    char mainmenu_Choice; // for storing mainmenu choice in main function
    char questmenu_Choice; // questmenu choice 
    displayInstructions(); // display game information 
    player = initializeCharacters(); // initializes the "player" struct

    do // Main game loop starts
    {
        mainmenu_Choice = display_Menu(); // takes choice from display menu function
        if (mainmenu_Choice == '1') // 1. Engage in Quests
        {
            questmenu_Choice = display_questsMenu(); // For quest #1
            if (questmenu_Choice == 1)
            {
                display_HeroInformation(player);
                Quest questResult = quest_1(player, Monsters); // creates a result varialbe with Quest datatype
                if (questResult.exitQuest) // if the user wishes to exit the quest amid battling.
                {
                    continue;
                }
            }
            else if (questmenu_Choice == 2)
            {
                display_HeroInformation(player);
                Quest questResult = quest2(player, Monsters);
                if (questResult.exitQuest)
                {
                    continue;
                }
            }
            else if (questmenu_Choice == 3) // For quest #3
            {
                display_HeroInformation(player);
                Quest questResult = quest3(player, Monsters);
                if (questResult.exitQuest)
                {
                    continue;
                }
            }
            else if (questmenu_Choice == 4) // if the user decides to exit the game.
            {
                continue;
            }
        }
        else if (mainmenu_Choice == '2') // Displays Hero information
        {
            display_HeroInformation(player);
        }
        else if (mainmenu_Choice == '3')
        {
            displayInventory(player);
        }
        else if (mainmenu_Choice == '4') // setting game color 
        {
            system("cls");
            setGameColor();
        }
        else if (mainmenu_Choice == '5') // exiting game
        {
            char exit_choice;
            cout << "\nAre you sure you want to exit the game? (Y or N): ";
            cin >> exit_choice;
            if (exit_choice == 'y' || exit_choice == 'Y')
            {
                return 0;
            }
            else if (exit_choice == 'n' || exit_choice == 'N')
            {

            }
            else
            {
                cout << "Invalid choice. Press Enter to go back to the main menu." << endl;
                system("pause");

            }
        }
    } while (true);
}
void setColor(int colorCode)
{
    cout << "\033[" << colorCode << "m";
    cin.get();
}

void resetColor()
{
    cout << "\033[0m";
}

int chooseColor()
{
    int colorChoice;
    cout << "Choose a color for the game:" << endl;
    cout << "1. Red\n2. Green\n3. Blue\n4. Cyan\n5. Default\n";
    cout << "Enter the corresponding number: ";
    cin >> colorChoice;
    switch (colorChoice)
    {
    case 1:
    {
        cout << "Color: Red" << endl;
        return 31;
        break;
    }
    case 2:
    {
        cout << "Color: Green" << endl;
        return 32;
        break;
    }
    case 3:
    {
        cout << "Color: Blue" << endl;
        return 34;
        break;
    }
    case 4:
    {
        cout << "Color: Cyan" << endl;
        return 36;
    }
    case 5:
    {
        cout << "Color: Default (white)" << endl;
        return 37;

    }
    default:
    {
        cout << "Invalid input, try again...." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return chooseColor();
    }
    }

}

void setGameColor()
{
    globalColor = chooseColor();
    setColor(globalColor);
}
void displayInstructions()
{
    // writing a pretty Teraxia font

    cout << setw(80) << "_________ _______  _______  _______          _________ _______ \n";
    cout << setw(80) << "\\__   __/(  ____ \\(  ____ )(  ___  )|\\     /|\\__   __/(  ___  )\n";
    cout << setw(80) << "   ) (   | (    \\/| (    )|| (   ) |( \\   / )   ) (   | (   ) |\n";
    cout << setw(80) << "   | |   | (__    | (____)|| (___) | \\ (_) /    | |   | (___) |\n";
    cout << setw(80) << "   | |   |  __)   |     __)|  ___  |  ) _ (     | |   |  ___  |\n";
    cout << setw(80) << "   | |   | (      | (\\ (   | (   ) | / ( ) \\    | |   | (   ) |\n";
    cout << setw(80) << "   | |   | (____/\\| ) \\ \\__| )   ( |( /   \\ )___) (___| )   ( |\n";
    cout << setw(80) << "   )_(   (_______/|/   \\__/|/     \\||/     \\|\\_______/|/     \\|\n";

    cout << "\n\nStep into the enchanting realm of Teraxia, where daring adventurers set forth on quests to achieve legendary hero \nstatus. Within this text-based RPG, players craft their characters, traverse the expansive world, partake in battles,\nand conquer quests. With its dynamic storytelling, character development, and an array of quests, the game promises an immersive experience, captivating players in the fantastical landscape.";
    cout << "\n\n--> Press Enter to go to class selection...";
    cin.get();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}

Hero initializeCharacters()
{
    Hero character;
    int class_choice;
    char confirmation_choice;
    system("cls");
    cout << setw(80) << "   _____ _                  _____      _           _   _             \n";
    cout << setw(80) << "  / ____| |                / ____|    | |         | | (_)            \n";
    cout << setw(80) << " | |    | | __ _ ___ ___  | (___   ___| | ___  ___| |_ _  ___  _ __  \n";
    cout << setw(80) << " | |    | |/ _` / __/ __|  \\___ \\ / _ \\ |/ _ \\/ __| __| |/ _ \\| '_ \\ \n";
    cout << setw(80) << " | |____| | (_| \\__ \\__ \\  ____) |  __/ |  __/ (__| |_| | (_) | | | |\n";
    cout << setw(80) << "  \\_____|_|\\__,_|___/___/ |_____/ \\___|_|\\___|\\___|\\__|_|\\___/|_| |_|\n";

    cout << "\n-> Please Enter your Username: ";
    int alphabet_counter = 0; // to check if username has atleast 3 digits 
    int spaces = 0; // to check if username doesn't have spaces
    do
    {

        getline(cin, character.user_name);
        alphabet_counter = 0;
        spaces = 0;
        for (int i = 0;i < character.user_name.size();i++)
        {
            if (isalpha(character.user_name[i])) // checks for alphabet in string
            {
                alphabet_counter++;
            }
            if (character.user_name[i] == ' ')
            {
                spaces++;
            }
        }
        if (alphabet_counter < 3) // if username has less than 3 alphabets
        {
            cout << "\nInvalid. Username must have atleast 3 alphabets.";
            cout << "\n-> Enter your username again: ";
            continue;
        }
        if (spaces != 0) // if username has any space 
        {
            cout << "\nInvalid. Username must have not have spaces.";
            cout << "\n-> Enter your username again: ";
            continue;
        }
        else if (character.user_name.size() >= 3 && character.user_name.size() <= 16)
        {
            char username_choice; // confirmation
            cout << "\nAre you sure you want to select username \"" << character.user_name << "\" ?: (Y/N): ";
            cin >> username_choice;
            if (username_choice == 'Y' || username_choice == 'y')
            {
                cout << "\nUsername has been set successfully.";
                cout << "\nUsername: " << character.user_name;
                break;
            }
            else
            {
                cout << "\n-> Please enter username again: ";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
            }
        }
        else if (!(character.user_name.size() >= 3 && character.user_name.size() <= 16)) // if not between 3 and 16  characters
        {
            cout << "Invalid. Username must be between 3 and 16 characters.";
            cout << "\nEnter your username again: ";
        }

    } while (true);

    cout << "\n\nIn this world of Teraxia, there are all grades of people wandering. You can play either of the following unique classes, each one possessing unique abillites:";
    cout << "\n\n1. Barbarian:\n--> Information: In the untamed realms of Teraxia, a Barbarian strides boldly into the fray. This formidable warrior is a force of sheer power and primal aggression. Standing tall with a muscular build and adorned in rugged, battle-worn armor, he emanates an aura of relentless determination. Having health points the greatest among the three classes, A barbarian is ready unleashing a furious onslaught that strikes terror into the hearts of enemies. A Barbarian has 200 healthpoints.";
    cout << "\n\n2. Warlock:\n--> Information: In the shadows where arcane secrets dwell, a figure emerges, veiled in mystery and wielding the dark arts. Known as a Warlock, this enigmatic spellcaster is a master of forbidden magic and eldritch powers. Cloaked in dark robes adorned with occult symbols, they exudes an air of mystique and malevolence. Although not the best in defense, but his powers sure do come in handy. A Warlock has 100 healthpoints.";
    cout << "\n\n3. Outlaw:\n--> Information: In the lawless expanses of our game world strides an Outlaw, a figure shrouded in defiance and driven by the thrill of rebellion. Known by the moniker \"Outlaw\", this daring renegade navigates the blurred lines between right and wrong with an air of cunning and bravado. Outlaws are the most cunning species in Teraxia.\nA Outlaw has 150 healthpoints.";
    cout << "\n\n--> Select class according to corresponding digit: ";
    do
    {
        confirmation_choice = 'N';
        cin >> class_choice;
        if (!(class_choice == 1 || class_choice == 2 || class_choice == 3 || class_choice == 4)) // invalid input if the entered digit is not either 1,2,3
        {
            cout << "Invalid input, Please try again: ";
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            continue;
        }
        if (class_choice == 1)
        {
            cout << "Are you sure you want to select the \"Barbarian\" class: ";
            cin >> confirmation_choice;
            if (confirmation_choice == 'y' || confirmation_choice == 'Y')
            {
                // Barbarian class 
                character.class_type = "Barbarian";
                character.health_points = 200;
                character.exp_points = 0;
                character.maxHealth = 200;
                cout << "\nYou have selected the class \"Barbarian\".";
                cout << "\n-> Press Enter to proceed to main menu...";
                cin.get();
                cin.ignore();
                break;
            }
            else
            {
                cout << "Select Again:";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                confirmation_choice = 'N';
                continue;
            }
        }
        else if (class_choice == 2)
        {
            cout << "Are you sure you want to select the \"Warlock\" class: ";
            cin >> confirmation_choice;
            if (confirmation_choice == 'y' || confirmation_choice == 'Y')
            {
                // Warlock class 
                character.class_type = "Warlock";
                character.health_points = 100;
                character.exp_points = 0;
                character.maxHealth = 100;
                cout << "\nYou have selected the class \"Warlock\".";
                cout << "\n-> Press Enter to proceed to main menu...";
                cin.get();
                cin.ignore();
                break;
            }
            else
            {
                cout << "Select Again:";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                confirmation_choice = 'N';
                continue;
            }
        }
        else if (class_choice == 3)
        {
            cout << "Are you sure you want to select the \"Outlaw\" class: ";
            cin >> confirmation_choice;
            if (confirmation_choice == 'y' || confirmation_choice == 'Y')
            {
                // Outlaw class
                character.class_type = "Outlaw";
                character.health_points = 150;
                character.exp_points = 0;
                character.maxHealth = 150;
                cout << "\nYou have selected the class \"Outlaw\".";
                cout << "\n-> Press Enter to proceed to main menu...";
                cin.get();
                cin.ignore();
                break;
            }
            else
            {
                cout << "Select Again:";
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                confirmation_choice = 'N';
                continue;

            }
        }

    } while (confirmation_choice == 'n' || confirmation_choice == 'N');


    character.inventorySize = 0;
    return character; // returns the character to "player" variable in main menu
}

void gainExperience(Hero& character, int xp)
{
    character.exp_points += xp;
    if (character.exp_points >= character.level * 100) // if character exceed limit of level exp
    {
        levelUp(character); // calls function levelling up!
    }
}

Hero levelUp(Hero& character)
{
    character.level++;
    int healthIncrease = 50;
    character.maxHealth += healthIncrease;  // Increase maxHealth by 50
    character.health_points = character.maxHealth;  // Set health_points to maxHealth

    cout << "\n-> Congratulations! You have leveled up to " << character.level;
    cout << "\n-> Your health has been increased to " << character.maxHealth;
    character.exp_points = 0;
    return character;
}

void display_HeroInformation(Hero& character)
{
    system("cls");
    cout << "  _    _                  _____        __                           _   _             \n";
    cout << " | |  | |                |_   _|      / _|                         | | (_)            \n";
    cout << " | |__| | ___ _ __ ___     | |  _ __ | |_ ___  _ __ _ __ ___   __ _| |_ _  ___  _ __  \n";
    cout << " |  __  |/ _ \\ '__/ _ \\    | | | '_ \\|  _/ _ \\| '__| '_ ` _ \\ / _` | __| |/ _ \\| '_ \\ \n";
    cout << " | |  | |  __/ | | (_) |  _| |_| | | | || (_) | |  | | | | | | (_| | |_| | (_) | | | |\n";
    cout << " |_|  |_|\\___|_|  \\___/  |_____|_| |_|_| \\___/|_|  |_| |_| |_|\\__,_|\\__|_|\\___/|_| |_|\n";
    cout << "                                                                                      \n";
    cout << "                                                                                      \n";
    cout << "\n-> Username: " << character.user_name;
    cout << "\n-> Class: " << character.class_type;
    cout << "\n-> Health points: " << character.maxHealth;
    cout << "\n-> Level: " << character.level;
    cout << "\n-> Experience points: " << character.exp_points << "XP";

    cout << "\nPress Enter to exit Profile Menu: ";
    cin.get();
    cin.ignore(INT_MAX, '\n');
}
void displayInventory(Hero& character)
{
    system("cls");
    cout << setw(80) << " _____                      _                   \n";
    cout << setw(80) << "|_   _|                    | |                  \n";
    cout << setw(80) << "  | |  _ ____   _____ _ __ | |_ ___  _ __ _   _ \n";
    cout << setw(80) << "  | | | '_ \\ \\ / / _ \\ '_ \\| __/ _ \\| '__| | | |\n";
    cout << setw(80) << " _| |_| | | \\ V /  __/ | | | || (_) | |  | |_| |\n";
    cout << setw(80) << "|_____|_| |_|\\_/ \\___|_| |_|\\__\\___/|_|   \\__, |\n";
    cout << setw(80) << "                                            __/ |\n";
    cout << setw(80) << "                                           |___/ \n";
    if (character.inventorySize == 0)
    {
        cout << "Empty\n";
    }
    else
    {
        for (int i = 0; i < character.inventorySize; ++i)
        {
            cout << i + 1 << ". " << character.inventory[i] << "\n";
        }
    }
    cout << "\n-> Press Enter to exit inventory...";
    cin.get();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

}
void addtoInventory(Hero& character, const  string& item) // const is used so that the original string isnt modified
{
    character.inventory[character.inventorySize++] = item;
    cout << "\n-> You obtained: " << item << endl;
}
int display_Menu()
{
    char choice;
    system("cls"); // clear screen 
    cout << setw(80) << "  __  __       _         __  __                  \n";
    cout << setw(80) << " |  \\/  |     (_)       |  \\/  |                 \n";
    cout << setw(80) << " | \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _ \n";
    cout << setw(80) << " | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |\n";
    cout << setw(80) << " | |  | | (_| | | | | | | |  | |  __/ | | | |_| |\n";
    cout << setw(80) << " |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n";
    cout << setw(80) << "                                                  \n";
    cout << setw(80) << "                                                  \n";
    cout << "\n1. Engage Quests";
    cout << "\n2. Open Profile";
    cout << "\n3. View Inventory ";
    cout << "\n4. Change Color";
    cout << "\n5. Exit Game";
    cout << "\n\nSelect Option: ";
    cin >> choice;
    if (choice == '1' || choice == '2' || choice == '3' || choice == '4' || choice == '5')
    {
        return choice;
    }
    else
    {
        cout << "Invalid choice, Try again please...";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin.get();
        return display_Menu();
    }
}

int display_questsMenu()
{
    int questmenu_Choice;
    system("cls");
    cout << setw(80) << "   ____                  _     __  __                  \n";
    cout << setw(80) << "  / __ \\                | |   |  \\/  |                 \n";
    cout << setw(80) << " | |  | |_   _  ___  ___| |_  | \\  / | ___ _ __  _   _ \n";
    cout << setw(80) << " | |  | | | | |/ _ \\/ __| __| | |\\/| |/ _ \\ '_ \\| | | |\n";
    cout << setw(80) << " | |__| | |_| |  __/\\__ \\ |_  | |  | |  __/ | | | |_| |\n";
    cout << setw(80) << " \\___\\_\\\\__,_|\\___||___/\\__| |_|  |_|\___|_| |_|\\__,_|\n";
    cout << setw(80) << "                                                        \n";
    cout << setw(80) << "                                                        \n";

    cout << "\n1. A Friend in Need is a Friend Indeed (Easy):";
    cout << "\n-> Objective: Rescue your ally from the claws of the wicked enemies. Fight bandits and free your friend from the chains";

    cout << "\n\n2. Purging the Bandits (Medium):";
    cout << "\n-> Objective: Save a local town from the vandilization of Bandits! Find clues and kill the local bandits";
    cout << "\n\n3. The Forbidden Temple's Curse (Hard):";
    cout << "\n-> Objective: Explore a path to the a temple, encountering different challenges, and figure out the mystery behind it!";

    cout << "\n\n4. Go back to Main Menu. ";
    cout << "\nSelect Option: ";
    do
    { // using loop in case choice is invalid
        cin >> questmenu_Choice;
        cin.clear(); // clear error flags
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (questmenu_Choice == 1 || questmenu_Choice == 2 || questmenu_Choice == 3 || questmenu_Choice == 4)
        {
            return questmenu_Choice;
        }
        else
        {
            cout << "Invalid option, try again: ";
            cin.clear(); // clear error flags

        }
    } while (true);
}
Quest quest_1(Hero& character, Monster& monsters)
{
    system("cls");
    char riddle_choice;
    bool completed_Riddle = false;
    Quest result; // stores the exit quest function 

    cout << setw(80) << "   ____                  _       _  _  __ \n";
    cout << setw(80) << "  / __ \\                | |    _| || |/_ |\n";
    cout << setw(80) << " | |  | |_   _  ___  ___| |_  |_  __  _| |\n";
    cout << setw(80) << " | |  | | | | |/ _ \\/ __| __|  _| || |_| |\n";
    cout << setw(80) << " | |__| | |_| |  __/\__ \\ |_  |_  __  _| |\n";
    cout << setw(80) << "  \\___\\_\\__,_|\\___||___/\\__|   |_||_| |_|\n";

    cout << "\n\nOur hero starts from his home, making his way through the Forbidden Forest, encountering obstacles\n"
        "as he wanders.";
    cout << "\n\n-> Press Enter to progess further in the quest: ";
    cin.get(); // takes input (Enter key)
    cout << "Not soon after starting his journey, our hero gets lost. Soon, he spots a weird stranger.\n"
        "This stranger offers our hero a chance to answer a riddle in return to find his way back ";
    cout << "\n\n-> Do you want to play the stranger's riddle?(Y or N): ";
    cin >> riddle_choice;
    if (riddle_choice == 'y' || riddle_choice == 'Y')
    {
        string riddle_guess;
        int counter = 3;
        cout << "\nHere goes the Riddle!";
        cout << "\nIm a box with a treasure inside. To open me up, what must you provide?: ";
        cin >> riddle_guess;
        while (true)
        {
            if (riddle_guess == "Key" || riddle_guess == "key")
            {
                cout << "You guessed the stranger's Riddle! The answer was Key" << endl;
                cout << "\nAs a reward, the stranger gives us a strange key. ";
                cout << "\nDo you want to accept this gift? ";
                char gift_Choice;
                cin >> gift_Choice;
                if (gift_Choice == 'y' || gift_Choice == 'Y')
                {
                    addtoInventory(character, "Strange Key");
                }
                completed_Riddle = true;
                if (counter == 3)
                {
                    gainExperience(character, 100);
                }
                else if (counter == 2)
                {
                    gainExperience(character, 75);
                }
                else if (counter == 1)
                {
                    gainExperience(character, 50);
                }
                break;
            }
            else
            {
                counter--;
                if (counter == 0)
                {
                    cout << "You missed the stranger's hint! Now you are on your own" << endl;
                    completed_Riddle = false;
                    break;
                }
                cout << "Wrong answer. The stranger is disappointed but gives you " << counter << " tries.";
                cout << "\nTry again: ";
                cin >> riddle_guess;
            }

        }
    }
    else if (riddle_choice == 'N' || riddle_choice == 'n')
    {
        cout << "You rejected the stranger's opportunity." << endl;
        completed_Riddle = false;
    }
    else
    {
        cout << "Invalid option. Missed the opportunity." << endl;
        completed_Riddle = false;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

    }
    cout << "\n";
    system("pause");
    if (completed_Riddle == true)
    {
        cout << "You successfully unraveled the riddle posed by the stranger, who then directed you toward the whereabouts of the Leviathan Camp."
            "However, he earnestly cautioned you about the perils that await on your forthcoming path. Undeterred, our hero presses on with the journey." << endl;
        cout << "\n";
        system("pause");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');


        cout << "\nAfter take guidance from the stranger, our Hero finally make their way out of the Forbidden Forest\n"
            "Soon after leaving the Forest, our Hero spots a strange bunker. Out of curiosity, our Hero enters the temple\n"
            "Not later, our Hero realizes it's a trap laid by the Leviathans!";
        cout << "\nThere are 5 doors which lead to the exit, but either one of them can be a deadly trap. Choose wisely!";
        cout << "\n-> Press Enter to continue: ";
        cin.get();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        int maze_choice;
        int real_door;
        real_door = rand() % 5 + 1;
        do
        {
            cout << "\n-> Select a door out of the three labelled 1,2,3,4 or 5 : ";
            cin >> maze_choice;
            if (maze_choice == real_door)
            {
                cout << "\nYou escaped the temple!";
                gainExperience(character, 100);
                break;
            }
            else if (maze_choice != real_door)
            {
                cout << "\nWrong door, try again!";
            }
            else
            {
                cout << "Invalid option. Try again";
            }
        } while (true);
        cout << "\n-> Press Enter to continue: ";
        cin.get();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nAfter narrowly escaping the bunker, Our hero continue their path to the Leviathan camp.\n"
            "After a long journey, our Hero finally arrives at the camp, hearing the warcries of the \n"
            "Leviathans. It is time to end this!";
        cout << "\n-> Press Enter to continue: ";
        cin.get();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        bool victory = false;
        do
        {

            display_battle1_instructions();
            Quest result = battle_quest1(character, monsters);
            if (result.exitQuest)
            {
                return result;
            }
            else
            {
                cout << "\n-> Here comes another Leviathan! Terminate it quickly!";
                cout << "\n-> Press Enter to continue: ";
                cin.ignore();
                cin.get();
                Quest result = battle_quest1(character, monsters);
                if (result.exitQuest)
                {
                    return result;
                }
                else
                {
                    cout << "\n-> Only one remains. Let's end this!";
                    cout << "\n-> Press Enter to continue: ";
                    cin.ignore();
                    cin.get();
                    Quest result = battle_quest1(character, monsters);
                    if (result.exitQuest)
                    {
                        return result;
                    }
                }

                if (character.health_points > 0)
                {
                    victory = true;

                    if (victory == true)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
        } while (true);
        cout << "\n-> Press Enter to continue: ";
        cin.get();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\n\nWith the Leviathan threat eliminated, peace begins to return to the Forbidden Forest. Draken, now free,\n"
            "offers to guide our Hero back to their village, sharing tales of the mystical creatures and ancient wonders\n"
            "that inhabit the enchanted realm of Teraxia.";
        cout << "\n\nAs a reward, Draken shares his hidden treasure, a \"Eclipse Crystal\", which is said to have godly\n"
            "hidden powers for whoever wields it!";
        gainExperience(character, 250);
        addtoInventory(character, "Eclipise Crystal");
        cout << "\n-> Press Enter to exit the quest: ";
        cin.get();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (completed_Riddle == false)
    {
        cout << "\nHaving missed the stranger's guidance, our hero begins to wander around again and tries to\n"
            "find where he is, It is already night and the Forest gets more dangerous at this time.\n"
            "Suddenly, our hero notices a dusty map lying on the wet grass.";

        bool map_choice;
        do
        {
            char gamemap_choice;
            cout << "\n-> Do you want to pick up the dusty map (Y or N): ";
            cin >> gamemap_choice;
            if (gamemap_choice == 'Y' || gamemap_choice == 'y')
            {
                map_choice = true;
                break;
            }
            else if (gamemap_choice == 'N' || gamemap_choice == 'n')
            {
                map_choice = false;
                break;
            }
            else
            {
                cout << "Invalid map choice. Try again... ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }

        } while (true);

        if (map_choice == true)
        {
            char backstory_choice;
            char quit_choice;
            addtoInventory(character, "Dusty Map"); // adds to inventory
            cout << "\nOur hero picks up the map, and is in shock to find out that the\n"
                "map leads to the Leviathan camp which is located not far away from his place.";
            cout << "Our hero guides his own way using the map in his hand through the Forest.";
            gainExperience(character, 50); // gains exp from collecting the map.

            cout << "\n-> Do you want to know the backstory of the Forbidden Forest(will get bonus xp)? (Y or N): ";
            cin >> backstory_choice;
            if (backstory_choice == 'y' || backstory_choice == 'Y')
            {
                cout << "\n-> Long ago, in the mystical realm of Teraxia, the Forbidden Forest stood as a mysterious and enchanted expanse,\n"
                    "shrouded in ancient magic and veiled by the secrets of time. Legends spoke of its origins, tracing back to the\n"
                    "era when powerful wizards and magical beings roamed the land. The Forbidden Forest is famous in whole Teraxia for\n"
                    "its shrouded mysteries and all sorts of evil entities lurking." << endl;
                gainExperience(character, 25);
            }
            cout << "\nSoon after finding the map, Our hero finally gets back on their path and continue forward to the\n"
                "Leviathan Camp. He finally crosses all Forbidden Forest and spots the Leviathan camp in the distance.\n";

            cout << "\n-> Press Enter to Progress:";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\nAfter seeing the camp, Our hero hears the screams of Leviathans from the camp, which meant they spotted\n"
                "our hero. They approach the hero, as they get prepared for the final battle!";
            cout << "\n-> Press Enter to Continue: ";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool victory = false;
            do
            {

                display_battle1_instructions();
                Quest result = battle_quest1(character, monsters);
                if (result.exitQuest)
                {
                    return result;
                }
                else
                {
                    cout << "\n-> Another one! Terminate it quickly!";
                    cout << "\n-> Press Enter to continue: ";
                    cin.ignore();
                    cin.get();
                    Quest result = battle_quest1(character, monsters);
                    if (result.exitQuest)
                    {
                        return result;
                    }
                }
                if (character.health_points > 0)
                {
                    victory = true;

                    if (victory == true)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            } while (true);

            cout << "\n\nAfter finally slaying the lasts of the Leviathan, our Hero basks in victory, freeing Draken from\n"
                "chains of cruelty and setting him free. Draken, now released from captivity, expressed his gratitude\n"
                "towards our Hero for their courage and determination.";
            cout << "\n-> Press Enter to continue: ";
            cin.ignore();
            cin.get();
            cout << "\n\nWith the Leviathan threat eliminated, peace begins to return to the Forbidden Forest. Draken, now free,\n"
                "offers to guide our Hero back to their village, sharing tales of the mystical creatures and ancient wonders\n"
                "that inhabit the enchanted realm of Teraxia.";
            cout << "\n\nAs a reward, Draken shares his hidden treasure, a \"Eclipse Crystal\", which is said to have godly\n"
                "hidden powers for whoever wields it!";
            gainExperience(character, 250);
        }
        else if (map_choice == false)
        {
            cout << "\nAfter our hero decided not to pick up the map due to its sketchiness, they traverse on their\n"
                "path. Feeling a bit scared of the atmosphere, our Hero hopes to locate the Leviathan Camp as\n"
                "as possible:  " << endl;
            system("pause");

            cout << "\n\nSuddenly, our Hero spots a weird treasure box at the bank of a nearby dirty pond. When they open \n"
                "the treasure box, it was full of personal items of Draken and piece of parchement. On opening the parchement\n"
                "it was Draken's letter before getting abducted by the Leviathans.";
            cout << "\n-> Press Enter to continue:";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\nIt appears Draken already knew he was getting abducted? or was it a fake letter? Nevertheless\n"
                "the letter mentioned about himself knowing that he will get kidnapped by Leviathans due to persoanl\n"
                "vendetta. There seem to be a precious gem in the box, probably left by Draken for us.";
            char gem_choice;
            cout << "\n-> Do you want to pick up the precious gem? (Y/N): ";
            do
            {
                cin >> gem_choice;
                if (gem_choice == 'Y' || gem_choice == 'y')
                {
                    addtoInventory(character, "Precious Gem");
                    break;
                }
                else if (gem_choice == 'N' || gem_choice == 'n')
                {

                }
                else
                {
                    cout << "Invalid choice. Retry: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            } while (true);
            cout << "\n-> Press Enter to continue:";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nAfter reading Draken's letter, our hero mounts up his strength and dedication again and makes\n"
                "way through the dark, creepy Forbidden Forest. Soon, he spots a white spot far in the distance.\n"
                "Upon seeing it up closely, It was actually a corpse of a dead Unicorn.";
            char unicorn_choice;
            cout << "\n\n-> Do you want to know about Unicorns in Teraxia? (bonus xp): ";
            cin >> unicorn_choice;
            if (unicorn_choice == 'y' || unicorn_choice == 'Y')
            {
                cout << "\n\nIn the mystical land of Terraria, hidden deep within the Celestial Glades, roams a herd of radiant unicorns,\n"
                    "guardians of the purest magic in the realm. These unicorns, adorned with resplendent coats that shimmer like\n"
                    "the evening sky, are the keepers of the legendary Crystal Grove—a sacred place where crystalline flora emanate\n"
                    "a magic that has sustained Terraria for centuries.";
                gainExperience(character, 25);
            }
            cout << "\n\nIt appears that the Unicorn is slayed by someone or something. Unicorns are one of the most purest\n"
                "magical beings in Teraxia. Only something abominable like the Leviathans would do such a act.\n"
                "Witnessing this, our Hero realized that he was getting more closer to the Leviathan Camp.";
            cout << "\nPress Enter to continue:";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOh No! It's a trap! The Leviathans laid a trap for anyone who will encounter the dead Unicorn";
            cout << "\nOur hero falls down a trench and sees that there are 4 steps where he can step and escape the trench\n";
            "but only of them is a real step and the other 3 are death";
            system("pause");
            cout << "\nYou must choose which trap is real of them all(1,2,3 or 4)!";
            cout << "\nYou will get more xp points if you do it with lesser tries.";
            int random_step;
            int counter = 0;
            int actual_step = rand() % 4 + 1;
            do
            {

                cout << "\n->Select a random step: ";
                cin >> random_step;
                if (random_step == actual_step)
                {
                    cout << "\nYou selected the right step!";

                    if (counter == 0)
                    {
                        gainExperience(character, 125);
                    }
                    else if (counter == 1 || counter == 2 || counter == 3)
                    {
                        gainExperience(character, 100);
                    }
                    else if (counter > 4)
                    {
                        gainExperience(character, 75);
                    }
                    break;
                }
                else
                {
                    cout << "You died! But you can try again....";
                    counter++;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            } while (true);
            cout << "\nPress Enter to progress further: ";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nAfter finally getting out of the trap, our hero finally makes his way through the Forbidden\n"
                "Forest locating the Leviathan Camp at a distance. Hearing the Leviathan war cries, our Hero prepares\n"
                "themselves for the final battle!";
            cout << "\n-> Press Enter to continue: ";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            bool victory = false;
            do
            {

                display_battle1_instructions();
                Quest result = battle_quest1(character, monsters);
                if (result.exitQuest)
                {
                    return result;
                }
                else
                {
                    cout << "\n-> Here comes another Leviathan! Terminate it quickly!";
                    cout << "\n-> Press Enter to continue: ";
                    cin.ignore();
                    cin.get();
                    Quest result = battle_quest1(character, monsters);
                    if (result.exitQuest)
                    {
                        return result;
                    }
                }
                if (character.health_points > 0)
                {
                    victory = true;

                    if (victory == true)
                    {
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            } while (true);
            cout << "\nPress Enter to continue: ";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\nWith the Leviathan threat eliminated, peace begins to return to the Forbidden Forest. Draken, now free,\n"
                "offers to guide our Hero back to their village, sharing tales of the mystical creatures and ancient wonders\n"
                "that inhabit the enchanted realm of Teraxia.";
            cout << "\n\nAfter finally slaying the lasts of the Leviathan, our Hero basks in victory, freeing Draken from\n"
                "chains of cruelty and setting him free. Draken, now released from captivity, expressed his gratitude\n"
                "towards our Hero for their courage and determination.";

            cout << "\n-> Press Enter to continue: ";
            cin.get();
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\n\nAs a reward, Draken shares his hidden treasure, a \"Eclipse Crystal\", which is said to have godly\n"
                "hidden powers for whoever wields it!";


            cout << "\n\nWith the Leviathan threat eliminated, peace begins to return to the Forbidden Forest. Draken, now free,\n"
                "offers to guide our Hero back to their village, sharing tales of the mystical creatures and ancient wonders\n"
                "that inhabit the enchanted realm of Teraxia.";
            cout << "\n\nAs a reward, Draken shares his hidden treasure, a \"Eclipse Crystal\", which is said to have godly\n"
                "hidden powers for whoever wields it!";
            addtoInventory(character, "Eclipise Crystal");
            gainExperience(character, 250);

        }
        cout << "\n-> Press Enter to exit the quest:";
        cin.get();
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else
    {
        cout << "Choice missed...";
        cin.get();
        cin.ignore();
    }
    return result;
}
Quest battle_quest1(Hero& character, Monster& monsters)
{
    Quest result;
    monsters.monsterHealth = 100; // leviathan health points are 100 
    do
    {
        int option;
        cout << "\n1. Fierce Attack" << endl;
        cout << "2. Defence" << endl;
        cout << "3. Exit quest" << endl;
        cout << "Choose your option: ";
        cin >> option;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (option)
        {
        case 1:
        {
            monsters.monsterDamage = ((rand() % 20) + 1); // generates random attacks for monsters(less damage)
            character.damage = ((rand() % 40) + 1); // generates random attacks for player(more damage)
            if (character.class_type == "Barbarian")// Setting more damager due to barbarian's higher hp
            {
                monsters.monsterDamage += 5;
            }
            else if (character.class_type == "Outlaw") // more damage for outlaw class
            {
                monsters.monsterDamage += 5;
            }


            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            if (character.damage >= monsters.monsterHealth)
            {
                monsters.monsterHealth = 0;
            }
            else
            {
                monsters.monsterHealth -= character.damage;
            }
            cout << "\nYou did " << character.damage << " damage to monster" << endl;
            cout << "The Leviathan has now " << monsters.monsterHealth << " hp left" << endl;
            if (monsters.monsterHealth == 0)
            {
                cout << "You killed the Leviathan!";
                gainExperience(character, 75);
                break;
            }
            cout << endl;
            system("pause");
            cout << "\nLeviathan did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " hp left" << endl;
            if (character.health_points <= 0)
            {
                cout << "You lost the battle, but you can try again!";
                continue;
            }
            break;
        }
        case 2:
        {
            monsters.monsterAttack = ((rand() % 20) + 1);

            if (monsters.monsterAttack >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterAttack;
            }
            cout << "In a result of defence monster did " << monsters.monsterAttack << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " HP" << endl;
            break;
        }
        case 3:
        {
            char quitchoice;
            cout << "Are you sure you want to exit? (Y/n): ";
            cin >> quitchoice;
            if (quitchoice == 'Y' || quitchoice == 'y')
            {
                result.exitQuest = true;
                return result;
            }
            break;
        }
        default:
        {
            cout << "Invalid Option. Try again!";
            break;
        }
        }

        if (monsters.monsterHealth <= 0)
        {

            break;
        }

    } while (true);

    result.exitQuest = false;
    return result;
}
void display_battle1_instructions()
{
    system("cls"); // clear screen 
    cout << "Leviathans are nasty breed of monsters, they usually come in packs.\n";
    cout << "\nIn this battle, you can either attack or defend. It's a Do or Die,\n"
        "means you will either win or you will die.";

}
Quest quest2(Hero& character, Monster& monsters)
{
    system("cls");
    Quest quest;
    cout << setw(80) << "   ____                  _       _  _  ___  \n";
    cout << setw(80) << "  / __ \\                | |    _| || ||__ \\ \n";
    cout << setw(80) << " | |  | |_   _  ___  ___| |_  |_  __  _| ) |\n";
    cout << setw(80) << " | |  | | | | |/ _ \\/ __| __|  _| || |_ / / \n";
    cout << setw(80) << " | |__| | |_| |  __/\__ \\ |_  |_  __  _/ /_ \n";
    cout << setw(80) << "  \\___\\_\\__,_|\\___||___/\\__|   |_||_||____|\n";

    cout << "\n\nIn the realm of Teraxia, you are a skilled adventurer known as \" " << character.user_name << " \".\n"
        << "You receive a plea for help from the local authorities. Bandits have established a dangerous hideout\n"
        "in the nearby woods, terrorizing travelers and merchants. It's time to embark on a quest to infiltrate\n"
        "the bandit hideout and bring an end to their criminal activities.\n";
    cout << "\nPress Enter to continue: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');


    cout << "\nAs our hero start their journey to the Bandit hideout, our hero face a critical decision...";
    cout << "\n1) Confront the bandits";
    cout << "\n2) Use stealth and approach quietly: ";
    cout << "\nChoose your action (1 or 2): ";
    bool willConfront;
    int playerChoice;
    do
    {
        cin >> playerChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (playerChoice == 1)
        {
            willConfront = true;
            break;
        }
        else if (playerChoice == 2)
        {
            willConfront = false;
            break;
        }
        else
        {
            cout << "Invalid option. Please select either 1 or 2....";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
    } while (true);
    if (willConfront)
    {
        cout << "\nOur hero picks the confrontation choice...";
        cin.get();
        cin.ignore();
        cout << "\nAfter picking confrontation, our hero makes way making themselves ready for a big battle\n"
            "Suddenly, a stray Bandit catches our hero by off-guard. The Bandit is armed seems to kill\n"
            "our hero, unless we solve the challenges posed by the bandit.";

        cout << "\n\nThe bandit offers us a series of challenges in order to spare your life: ";
        cout << "\nPress Enter to continue: ";
        cin.get();
        cin.ignore();
        string guess_sentence;
        int counter = 3;
        string target_sentence = "Teraxia";
        cout << "\nHere comes the first challenge: ";
        cout << "\nOur hero must encrypt the following characters into a sentence: ";
        cout << "\n--> Digits: 20 | 5 | 18 | 1 | 24 | 2 | 9 | 1";
        do
        {
            cout << "\nEnter a guess sentence: ";
            cin >> guess_sentence;
            if (guess_sentence == "teraxia" || guess_sentence == "Teraxia")
            {
                cout << "\nYou succesfully passed the first challenge.";
                // put gain experience here
                cout << "\nIt is time for the last challenge: " << endl;
                system("pause");
                string target_word = "death";
                string scrambled_word = target_word;


                random_shuffle(scrambled_word.begin(), scrambled_word.end());


                cout << "\nHere comes the next challenge: ";
                cout << "\nOur hero must unscramble the following word: ";
                cout << "\nScrambled Word: " << scrambled_word;


                string user_unscrambled_word;
                cout << "\nYour Answer: ";
                cin >> user_unscrambled_word;
                if (user_unscrambled_word == target_word)
                {
                    cout << "Bandit: Impressive! You've unscrambled the word correctly.\n";
                    // gain experience
                    break;
                }
                else
                {
                    counter--;
                    if (counter == 0)
                    {
                        cout << "\nYou failed Bandit's challenge and got killed.";
                        break;
                    }
                    cout << "Bandit: Wrong answer! Try again or face the consequences.\n";
                    cout << "\nYou have " << counter << "more tries.";
                    continue;
                }
            }
            else
            {
                counter--;
                if (counter == 0)
                {
                    cout << "\nYou failed Bandit's challenge and got killed.";
                    break;
                }
                cout << "\nIncorrect guess, but you can try again!";
                cout << "\nYou have " << counter << " more tries.";
            }
        } while (true);
        cout << "\nAfter guessing all the challenges, the bandit spares our life and also guides our hero\n"
            "to Bandit hideout. As a weird gesture, the bandit gives us a weird doll, probably from a previous raid.";
        addtoInventory(character, "Weird Doll");
        cout << "\nPress Enter to continue: ";
        cin.get();
        cin.ignore();
        cout << "\nAfter finally reaching the hideout, our hero prepares themselves to eliminate all the bandits!";
        cout << "\nPress Enter to continue: ";
        cin.get();
        cin.ignore();
        do
        {
            quest = battle_quest2(character, monsters);
            if (quest.exitQuest)
            {
                return quest;
            }
            else
            {
                cout << "\nAnother bandit joins the party, Eliminate this one too!" << endl;
                system("pause");
                quest = battle_quest2(character, monsters);
                if (quest.exitQuest)
                {
                    return quest;
                }
                cout << "\nAfter finally killing few of the bandits, the others ran away and soon the town was free\n"
                    "from the terror of the bandits. Peace finally came.";
                gainExperience(character, 200);
                break;
            }
        } while (true);

    }
    else if (willConfront == false)
    {
        cout << "\nAfter picking stealth, our hero makes way to the the hideout. After infiltrating the camp,\n"
            "our hero makes way to eliminate the bandit leader to divide the Bandits in one blow.\n"
            "Deep in the camp, our hero encounters a certain door which requires a lock to open it.\n";

        system("pause");
        int correct_combination = rand() % 100 + 1;
        int counter = 7;
        cout << "\nChallenge: Pick the lock to open the door without making a sound.";
        cout << "\nHint: The lock combination is a 2-digit number.";
        do
        {

            cout << "\nYour Guess: ";
            int user_guess;
            cin >> user_guess;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (cin.good())
            {
                if (user_guess == correct_combination)
                {
                    cout << "\nSuccessfull! You may proceed quietly.\n";
                    break;
                }
                else if (user_guess != correct_combination)
                {
                    if (user_guess > 0 && user_guess <= 100)
                    {
                        counter--;
                        if (counter == 0)
                        {
                            cout << "\nOut of Tries! You've triggered a silent alarm.\n" << endl;
                            cout << "\nDeal with the bandits!" << endl;
                            system("pause");
                            quest = battle_quest2(character, monsters);
                            if (quest.exitQuest)
                            {
                                return quest;
                            }
                            cout << "\nBandit: Reinforcements are coming! Proceed with caution.\n";
                            quest = battle_quest2(character, monsters);
                            if (quest.exitQuest)
                            {
                                return quest;
                            }
                            break;
                        }
                    }
                }
                if (user_guess < correct_combination)
                {
                    cout << "Try a bit higher!";
                }
                else if (user_guess > correct_combination)
                {
                    cout << "Try a bit lower!";
                }
                cout << "\nYou have " << counter << " tries remaining. ";
            }
            else
            {
                cout << "Invalid input. Please stop playing around....";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
        } while (true);
        cout << "\nAfter picking the lock, our hero sneaks up on the bandit leader, catching him off guard!";
        cout << "\nSlay the leader once and for all." << endl;
        system("pause");
        Quest result = bossbattle2(character, monsters);
        if (result.exitQuest)
        {
            return result;
        }
        cout << "\nAfter finally the Bandit Leader, the others ran away and soon the town was free\n"
            "from the terror of the bandits. Peace finally came. Our hero makes their way back to the village\n"
            "Our hero takes their loot from the Bandits, including a \"Divine Rapier\" ";
        addtoInventory(character, "Divine Rapier");
        gainExperience(character, 200);

    }
    cout << "\n-> Press Enter to exit the quest:";
    cin.get();
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    quest.exitQuest = false;
    return quest;
}
Quest battle_quest2(Hero& character, Monster& monsters)
{
    Quest result;
    system("cls");
    monsters.monsterHealth = 150;
    do
    {
        int option;
        cout << "\n1. Fierce Attack" << endl;
        cout << "2. Defence" << endl;
        cout << "3. Exit quest" << endl;
        cout << "Choose your option: ";
        cin >> option;
        if (!(option == 1 || option == 2 || option == 3))
        {
            cout << "Invalid choice, Try again.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (option)
        {
        case 1:
        {
            monsters.monsterDamage = ((rand() % 20) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 5;
            }
            if (character.class_type == "Outlaw")
            {
                monsters.monsterDamage += 5;
            }
            character.damage = ((rand() % 55) + 1);
            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            if (character.damage >= monsters.monsterHealth)
            {
                monsters.monsterHealth = 0;
            }
            else
            {
                monsters.monsterHealth -= character.damage;
            }
            cout << "\nYou did " << character.damage << " damage to the bandit" << endl;
            cout << "The bandit has now " << monsters.monsterHealth << " hp left" << endl;

            if (monsters.monsterHealth == 0)
            {
                cout << "You killed the Bandit!";
                result.lostBattle = false;
                break;
            }

            system("pause");
            cout << "\nBandit did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " hp left" << endl;

            if (character.health_points <= 0)
            {
                cout << "You lost the battle!";
                result.exitQuest = true;
                break;
            }

            break;
        }
        case 2:
        {
            monsters.monsterDamage = ((rand() % 10) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 10;
            }

            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            cout << "In a result of defence, Bandit did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " HP" << endl;
            break;
        }
        case 3:
        {
            char quitchoice;
            cout << "Are you sure you want to exit? (Y/n): ";
            cin >> quitchoice;
            if (quitchoice == 'Y' || quitchoice == 'y')
            {
                result.exitQuest = true;
                return result;
            }
            break;
        }
        default:
        {
            cout << "Invalid Option. Try again!";
            break;
        }
        }

    } while (monsters.monsterHealth > 0 && character.health_points > 0);
    result.exitQuest = false;
    return result;
}
Quest bossbattle2(Hero& character, Monster& monsters)
{
    Quest result;
    system("cls");
    monsters.monsterHealth = 300;
    cout << "\nThe Bandit leader will have greater hitpoints! Slay him and end the terror of the bandits.";
    do
    {
        int option;
        cout << "\n\n1. Fierce Attack" << endl;
        cout << "2. Defence" << endl;
        cout << "3. Exit quest" << endl;
        cout << "Choose your option: ";
        cin >> option;
        if (!(option == 1 || option == 2 || option == 3))
        {
            cout << "Invalid choice, Try again.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option)
        {
        case 1:
        {
            monsters.monsterDamage = ((rand() % 20) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 5;
            }
            if (character.class_type == "Outlaw")
            {
                monsters.monsterDamage += 5;
            }
            character.damage = ((rand() % 25) + 1);
            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            if (character.damage >= monsters.monsterHealth)
            {
                monsters.monsterHealth = 0;
            }
            else
            {
                monsters.monsterHealth -= character.damage;
            }
            cout << "\nYou did " << character.damage << " damage to the bandit" << endl;
            cout << "The bandit has now " << monsters.monsterHealth << " hp left" << endl;

            if (monsters.monsterHealth == 0) {
                cout << "You killed the Bandit Leader!";
                result.lostBattle = false;
                break;
            }

            system("pause");
            cout << "\nBandit did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " hp left" << endl;

            if (character.health_points <= 0)
            {
                cout << "You lost the battle!";
                result.lostBattle = true;
                break;
            }

            break;
        }
        case 2:
        {
            monsters.monsterDamage = ((rand() % 10) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 10;
            }

            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            cout << "In a result of defence, Bandit did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " HP" << endl;
            break;
        }
        case 3:
        {
            char quitchoice;
            cout << "Are you sure you want to exit? (Y/n): ";
            cin >> quitchoice;
            if (quitchoice == 'Y' || quitchoice == 'y')
            {
                result.exitQuest = true;
                return result;
            }
            break;
        }
        default:
        {
            cout << "Invalid Option. Try again!";
            break;
        }
        }

    } while (monsters.monsterHealth > 0 && character.health_points > 0);
}
Quest quest3(Hero& character, Monster& monsters)
{
    monsters.monsterHealth = 200;
    int battleAttempts = 0;
    Quest result;
    string dummy;
    system("cls");
    cout << setw(80) << "   ____                  _       _  _  ____  \n";
    cout << setw(80) << "  / __ \\                | |    _| || ||___ \ \n";
    cout << setw(80) << " | |  | |_   _  ___  ___| |_  |_  __  _|__) |\n";
    cout << setw(80) << " | |  | | | | |/ _ \\/ __| __|  _| || |_|__ < \n";
    cout << setw(80) << " | |__| | |_| |  __/\__ \\ |_  |_  __  _|__) |\n";
    cout << setw(80) << "  \\___\\_\\__,_|\\___||___/\\__|   |_||_||____/ \n";

    cout << "\n\nThe townspeople, burdened by the ominous aura emanating from the Forbidden Temple\n"
        "are paralyzed by fear. It is in this climate of uncertainty that a brave adventurer\n"
        "emerges, fueled by the desire to unravel the mysteries that have haunted Teraxia"
        " for generations.";

    cout << "\nPress Enter to continue: ";
    cin.get();
    cin.ignore();
    cout << "\nOur hero sets out on their journey, asking the local townsfolk for the\n"
        "direction of the Forbidden Temple. Although extremely warned by all people\n"
        "our hero remains resilient and devotes their life to exposing the mystery of the\n"
        "Forbidden Temple";
    cout << "\nPress Enter to continue: ";
    getline(cin, dummy);

    cout << "\nAfter entering the forest which faced heavy rain, it was filled with puddles of\n"
        "muddy water. It was extremely hard to move in such conditions. But determined\n"
        "our hero saw the path leading to two other paths, left and right. They must\n"
        "make a choice which path to choose.";
    char path_choice;
    bool rightPath;
    cout << "\nWhich path do you want to pick, Left or Right (L/R): ";
    do {
        cin >> path_choice;
        if (path_choice == 'L' || path_choice == 'l') {
            rightPath = false;
            break;
        }
        else if (path_choice == 'R' || path_choice == 'r')
        {
            rightPath = true;
            break;
        }
        else
        {
            cout << "Invalid choice. Please select either L or R: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (true);

    if (rightPath == true)
    {
        cout << "\nAfter choosing the right direction path, our hero stops for a moment to think where this\n"
            "path will lead to. Nevertheless, our hero presses on. Moving through dense forest with\n"
            "determination and courage.";

        cout << "\nAs our hero ventures deeper into the forest, they encounter a mysterious creature lurking\n"
            "among the trees. The creature has glowing eyes and an otherworldly presence." << endl;
        system("pause");
        cout << "\nOur hero must now decide how to deal with the mysterious creature. They can choose to\n"
            "confront the creature head-on (C) or try to sneak past it (S).";

        char decision;
        bool willFight;
        cout << "\nWhat will our hero do? Choose C to confront or S to sneak: ";
        do
        {
            cin >> decision;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (decision == 'C' || decision == 'c') {
                cout << "\nOur hero bravely confronts the creature, ready for a battle!";
                willFight = true;
                break;
            }
            else if (decision == 'S' || decision == 's') {
                cout << "\nOur hero decides to take a stealthy approach, attempting to sneak past the creature.";
                willFight = false;
                break;
            }
            else
            {
                cout << "Invalid choice. Please select either C or S: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        while (true);

        if (willFight == true)
        {
            bool retryBattle;
            do
            {
                result = battle_quest3(character, monsters);
                if (result.exitQuest == true)
                {
                    cout << "\nExiting...";
                    cin.get();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return result;
                }
                else if (result.lostBattle == true)
                {
                    battleAttempts++;
                    if (battleAttempts == 2)
                    {
                        cout << "\nExiting to main menu...";
                        cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');

                        return result;
                    }
                    cout << "\nYou can try again! Attempt: " << battleAttempts << "/2";
                    cout << "\nPress Enter to continue: ";
                    cin.get();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    monsters.monsterHealth = 200; // Reset monster health for a new battle
                    character.health_points = 100; // Reset player health for a new battle
                    retryBattle = (battleAttempts < 2 && !result.exitQuest);
                }
                else if (result.lostBattle == false)
                {
                    break;
                }
                else
                {
                    retryBattle = false;
                }
            } while (retryBattle);

            cout << "\nPress Enter to continue: ";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "\nAfter defeating the creature, our hero continues their journey. From killing the creature\n"
                "our hero cuts up the skin of the creature, using later for warmth or bait.";
            addtoInventory(character, "Warm Fur");
            cout << "\n\nOur hero finally arrives at the Forbidden Temple. Massive in size\n"
                "our hero stops to gaze at its millenia old structure. With determination\n"
                "our hero enters the Temple through a narrow door.";
            cout << "\nPress Enter to continue: ";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "\nThe air becomes heavy with an ancient and mysterious power\n"
                "The walls are adorned with faded murals, telling tales of"
                "a time long forgotten.";

            cout << "\nAfter traversing through a series of interconnected chambers,"
                "our hero encounters a puzzle blocking the way forward.\n"
                "Ancient inscriptions on the walls suggest that solving the puzzle will unveil the path to the temple's inner sanctum";

            cout << "\n\nIn order to solve this puzzle, our hero must answer all three\n"
                "of the riddles posed before us carved on the wall!";
            cout << "\nThere are only 2 chances, otherwise our hero will be killed!";
            cout << "\nPress Enter to continue: ";
            cin.get();
            string riddleguess1, riddleguess2, riddleguess3;
            cout << "Here goes the first riddle!";
            int riddle_chances = 2;
            do
            {
                cout << "\n\n\033[3m#1: I speak without a mouth and hear without ears.\n"
                    "I have no body, but I come alive with the wind\n"
                    "What am I? : \033[0m";
                cin >> riddleguess1;
                if (riddleguess1 == "Echo" || riddleguess1 == "echo")
                {
                    cout << "You guessed it!";
                    cout << "\nHere comes the second riddle! ";
                    cout << "\n\n\033[3m#2: I'm tall when I'm young, and short when I'm old.\n"
                        "What am I? (Hint: a object): \033[0m";
                    cin >> riddleguess2;
                    if (riddleguess2 == "candle" || riddleguess2 == "Candle")
                    {
                        cout << "\nGood job!";
                        cout << "\nIt's time for the last riddle. Be ready.\n";
                        cout << "\n\033[3m#3: I am not alive, but I can grow,\n"
                            "I don't have lungs, but I need air.\n"
                            "What am I? (Hint: it's warm'): \033[0m";
                        cin >> riddleguess3;
                        if (riddleguess3 == "Fire" || riddleguess3 == "fire")
                        {
                            cout << "\nYou guessed all of riddles!";
                            break;
                        }
                        else
                        {
                            riddle_chances--;
                            if (riddle_chances == 0)
                            {
                                cout << "\nYou lost the puzzle. Exiting to main menu...";
                                cin.get();
                                return result;
                            }
                            cout << "Wrong answer! Try again.";
                            cout << "\nYou have one last chance!" << endl;
                            system("pause");
                            continue;
                        }
                    }
                    else
                    {
                        riddle_chances--;
                        if (riddle_chances == 0)
                        {
                            cout << "\nYou lost the puzzle. Exiting to main menu...";
                            return result;
                        }
                        cout << "Wrong answer! Try again.";
                        cout << "\nYou have one last chance!" << endl;
                        system("pause");
                        continue;
                    }
                }
                else
                {
                    riddle_chances--;
                    if (riddle_chances == 0)
                    {
                        cout << "\nYou lost the puzzle. Exiting to main menu...";
                        return result;
                    }
                    cout << "Wrong answer! Try again.";
                    cout << "\nYou have one last chance!" << endl;
                    system("pause");
                    continue;
                }
            } while (riddle_chances < 2);

            cout << "\n\nAfter guessing all the riddles, our hero finally makes their way to the inner sanctum of the temple.\n"
                "As strolling, there are all kinds of ancient inscriptions on the walls, depicting the rich history of\n"
                "the temple and its mysterious past. The air inside the sanctum is thick with an otherworldly energy, and\n"
                "our hero senses that they are nearing the heart of the temple's secrets.";

            char story_choice;
            cout << "\n\nDo you want to know the backstory of the Forbidden temple? (bonus xp): ";
            cin >> story_choice;
            if (story_choice == 'y' || story_choice == 'Y')
            {
                cout << "\nIn the heart of Teraxia, an ancient land veiled in mystery, stands the Forbidden Temple—a relic of forgotten power.\n"
                    "Once tended by the Eldarans, a civilization attuned to magic and nature, the temple now whispers secrets lost to time.";

                cout << "\n\nLegends speak of an artifact within, the Heartstone, a crystal pulsating with the essence of the land. Guarded\n"
                    "by wards and concealed from the unworthy, the temple became a symbol of peril and promise.";
                gainExperience(character, 75); // gains experience if the user decides to be a nerd
            }
            cout << "\nAfter reaching center sanctum of the temple, our hero spots a flashing red light in a distance\n"
                "Going near the light, it appears to a red gem a size of a pumpkin. In a flash, our hero guessed that\n"
                "it was the mythical Heartstone! Its radiant glow casts a mesmerizing aura, illuminating the inner sanctum\n"
                "with hues of iridescent blues and greens." << endl;
            system("pause");

            cout << "\n\nWhen our hero took another step, suddenly he saw heard footsteps from behind. It was a mysterious\n"
                "creature cloaked in black hood. It must be the Temple Guardian. He will stop our hero from possessing\n"
                "the Heartstone at all costs. We must let not the Guardian hinder us.";

            cout << "\n\nThe Guardian has unknown healthpoints. Be aware!" << endl;

            system("pause");
            do
            {
                result = bossbattle_3(character, monsters);
                if (result.exitQuest)
                {
                    return result;
                }
                if (result.lostBattle == false)
                {
                    break;
                }
            } while (true);
        }
        else if (willFight == false)
        {
            cout << "\nAfter choosing not to fight and keep a stealthy stance, Our hero narrowly \n"
                "escapes the creature cunningly and continues their journey. After a short interval\n"
                "they finally spot the Forbidden Temple, massive in size and weird aura to be sensed.\n"
                "Nevertheless, our hero enters the temple" << endl;
            system("pause");

            cout << "\n\nAs our hero progresses deeper into the temple, they encounter a chamber with three pedestals,\n"
                "each representing an element - Fire, Water, and Earth. Enigmatic inscriptions on the walls provide\n"
                "a clue - \"Balance is the key to unlocking the path\" ";

            cout << "\n\nOur hero is tasked with placing three elemental orbs in three elemental pedestals, making balance" << endl;
            system("pause");

            do
            {
                bool puzzleCompleted;
                puzzleCompleted = puzzle_3(character);
                if (puzzleCompleted == true)
                {
                    gainExperience(character, 150);
                    break;
                }
            } while (true);
            cout << endl;
            system("pause");

            cout << "\nAfter passing through the chamber, our hero makes way to the inner sanctums of the temple. Suddenly, they spot a rare artefact known as \"Urn of Shadows\" which is rumored to give lucky fate to the possessor";
            cout << "\nDo you want to pick up the item? (Y/N): ";
            char item_choice;
            do
            {
                cin >> item_choice;
                if (item_choice == 'Y' || item_choice == 'y')
                {
                    addtoInventory(character, "Urn of Shadows");
                    break;
                }
                else if (item_choice == 'N' || item_choice == 'n')
                {

                }
                else
                {
                    cout << "Invalid choice. Retry: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    continue;
                }
            } while (true);
            cout << "Finally making it to the inner sanctum, our hero suddenly spots a flashing red light in the distance. Upon\n"
                "further look, it revealed to be the Legendary Heartstone!";

            cout << "\n\nPress Enter to continue: ";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');


            cout << "\n\nAs our hero approached to touch the Heartstone, they heard a noise behind the chamber. It revealed\n"
                "to be a mysterious figure robed in a Black Cloak. This must be the infamous Guardian Temple and is\n"
                "behind the disapperances happening in the Forbidden Temple. He will try his most to stop our hero from\n"
                "taking the HeartStone. We must defeat him!";

            cout << "\nPress Enter to continue: ";
            cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            do
            {
                result = bossbattle_3(character, monsters);
                if (result.exitQuest)
                {
                    return result;
                }
                else if (result.lostBattle == false)
                {
                    break;
                }

            } while (true);

        }
        cout << "\nPress Enter to continue...";
        cin.get();

        cout << "\n\nAfter finally defeating the Guardian Temple, our hero grabs the Heartstone\n"
            "still surprised by its unreal mystic aura. With the Heartstone, our hero sets\n"
            "back to their home, impatient to tell the whole town what had happened.";
        gainExperience(character, 400);
        addtoInventory(character, "Legendary Heartstone");
        cout << "\nPress Enter to exit the quest...";
        cin.get();
        return result;
    }
    else if (rightPath == false)
    {
        cout << "\nAfter picking the left direction path, our hero navigates through dense vegetation and\n"
            "finds themselves in a secluded part of the forest. The air is thick with an eerie silence,\n"
            "and the trees seem to close in around them, creating an almost claustrophobic atmosphere.";

        cout << "\nAs our hero ventures deeper into the mysterious forest, they come across an ancient\n"
            "ruin covered in vines and moss. The ruins emanate a strange energy, and our hero feels\n"
            "compelled to explore further.";

        cout << "\nPress Enter to continue: ";
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nInside the ruins, our hero discovers a series of chambers adorned with faded murals\n"
            "depicting a forgotten civilization. The walls tell a tale of a once-prosperous society that\n"
            "worshipped nature and magic. However, a dark force had descended upon them, leading to\n"
            "their downfall.";
        cout << "\nPress Enter to continue: ";
        cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\n\nAs our hero delves deeper into the ruins, they come across a mysterious altar at the center\n"
            "of a grand chamber. On the altar, three elemental orbs are placed - Fire, Water, and Earth.";

        cout << "\nA voice echoes in the chamber, 'To prove your worth, restore the balance that was lost.'\n"
            "Our hero realizes that they must place the orbs in the correct order to restore the balance\n";
        do
        {
            bool puzzleCompleted;
            puzzleCompleted = puzzle_3(character);
            if (puzzleCompleted == true)
            {
                gainExperience(character, 150);
                break;
            }
        } while (true);
        cout << "\nAfter sorting the challenge, another one comes in the path. Our hero must solve some logical\n"
            "questions. There are 3 in total!";
        cout << "\nPress Enter to continue: ";
        cin.get();
        cin.ignore();
        int answer;
        int lives = 3;
        cout << "\nHere comes the first challenge: ";
        cout << "\n\nWhat is the next number in the sequence 2, 3, 5, 8, 13";
        cout << "\n->State your answer: ";
        cin >> answer;
        if (answer == 21)
        {
            cout << "\nYou got the first correct!";
            cout << "\nHere comes the second riddle.";
            cout << "\n->What is 7 x 7 – 7 + 7 ?";
            cout << "\n->State your answer: ";
            cin >> answer;
            if (answer == 49)
            {
                cout << "\nYou got the second correct!";
                cout << "\nHere comes the last riddle.";
                cout << "\nWhat is half of two plus two?";
                cout << "\n->State your answer: ";
                cin >> answer;
                if (answer == 3)
                {
                    cout << "\nYou guessed all the riddles!";
                }
                else
                {
                    lives--;
                    if (lives == 0)
                    {
                        cout << "\nYou died from the trap!";
                        return result;
                    }
                    cout << "Incorrect. You lost a chance!";
                    cout << "You have " << lives << "lives left!";
                }
            }
            else
            {
                lives--;
                if (lives == 0)
                {
                    cout << "\nYou died from the trap!";
                    return result;
                }
                cout << "Incorrect. You lost a chance!";
                cout << "You have " << lives << "lives left!";
            }

        }
        else
        {
            lives--;
            if (lives == 0)
            {
                cout << "\nYou died from the trap!";
                return result;
            }
            cout << "Incorrect. You lost a chance!";
            cout << "You have " << lives << "lives left!";
        }
        cout << "\nAfter passing through the chamber, our hero finally reaches in the inner chambers of the temple\n"
            "Our hero suddenly spots a flashing red light in the distance. Upon\n"
            "further look, it revealed to be the Legendary Heartstone!";

        cout << "\n\nPress Enter to continue: ";
        cin.get();
        cin.ignore();

        cout << "\n\nAs our hero approached to touch the Heartstone, they heard a noise behind the chamber. It revealed\n"
            "to be a mysterious figure robed in a Black Cloak. This must be the infamous Guardian Temple and is\n"
            "behind the disapperances happening in the Forbidden Temple. He will try his most to stop our hero from\n"
            "taking the HeartStone. We must defeat him!";

        cout << "\nPress Enter to continue: ";
        cin.get();
        do
        {
            result = bossbattle_3(character, monsters);
            if (result.exitQuest)
            {
                return result;
            }
            else if (result.lostBattle == false)
            {
                break;
            }

        } while (true);

    }
    cout << "\nPress Enter to continue...";
    cin.get();

    cout << "\n\nAfter finally defeating the Guardian Temple, our hero grabs the Heartstone\n"
        "still surprised by its unreal mystic aura. With the Heartstone, our hero sets\n"
        "back to their home, impatient to tell the whole town what had happened.";
    gainExperience(character, 400);
    addtoInventory(character, "Legendary Heartstone");
    cout << "\nPress Enter to exit the quest...";
    cin.get();
    return result;
}
Quest battle_quest3(Hero& character, Monster& monsters)
{
    Quest result;
    monsters.monsterHealth = 100;
    system("cls");

    do
    {
        int option;
        cout << "\n1. Fierce Attack" << endl;
        cout << "2. Defence" << endl;
        cout << "3. Exit quest" << endl;
        cout << "Choose your option: ";
        cin >> option;
        if (!(option == 1 || option == 2 || option == 3))
        {
            cout << "Invalid choice, Try again.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (option)
        {
        case 1:
        {
            monsters.monsterDamage = ((rand() % 35) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 20;
            }
            if (character.class_type == "Outlaw")
            {
                monsters.monsterDamage += 10;
            }
            character.damage = ((rand() % 30) + 1);
            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            if (character.damage >= monsters.monsterHealth) {
                monsters.monsterHealth = 0;
            }
            else
            {
                monsters.monsterHealth -= character.damage;
            }
            cout << "\nYou did " << character.damage << " damage to the monster" << endl;
            cout << "The monster has now " << monsters.monsterHealth << " hp left" << endl;

            if (monsters.monsterHealth == 0) {
                cout << "You killed the monster!";
                result.lostBattle = false;
                gainExperience(character, 200);
                break;
            }

            system("pause");
            cout << "\nMonster did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " hp left" << endl;

            if (character.health_points <= 0)
            {
                cout << "You lost the battle!";
                result.lostBattle = true;
                break;
            }

            break;
        }
        case 2:
        {
            monsters.monsterDamage = ((rand() % 10) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 10;
            }

            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            cout << "In a result of defence, monster did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " HP" << endl;
            break;
        }
        case 3:
        {
            char quitchoice;
            cout << "Are you sure you want to exit? (Y/n): ";
            cin >> quitchoice;
            if (quitchoice == 'Y' || quitchoice == 'y')
            {
                result.exitQuest = true;
                return result;
            }
            break;
        }
        default:
        {
            cout << "Invalid Option. Try again!";
            break;
        }
        }

    } while (monsters.monsterHealth > 0 && character.health_points > 0);

    result.exitQuest = false;
    return result;
}
Quest bossbattle_3(Hero& character, Monster& monsters)
{
    Quest result;
    monsters.monsterHealth = 300;
    system("cls");
    do
    {
        int option;
        cout << "\n1. Fierce Attack" << endl;
        cout << "2. Defence" << endl;
        cout << "3. Exit quest" << endl;
        cout << "Choose your option: ";
        cin >> option;
        if (!(option == 1 || option == 2 || option == 3))
        {
            cout << "Invalid choice, Try again.";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        switch (option)
        {
        case 1:
        {
            monsters.monsterDamage = ((rand() % 40) + 1);

            if (character.class_type == "Barbarian") // Setting more damager due to barbarian's higher hp
            {
                monsters.monsterDamage += 20;
            }
            else if (character.class_type == "Outlaw") // more damage for outlaw class
            {
                monsters.monsterDamage += 10;
            }

            // damage for warlock will stay the same due to initial 100 hp of warlock.

            character.damage = ((rand() % 30) + 1);

            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            if (character.damage >= monsters.monsterHealth)
            {
                monsters.monsterHealth = 0;
            }
            else
            {
                monsters.monsterHealth -= character.damage;
            }
            cout << "\nYou did " << character.damage << " damage to the Guardian" << endl;
            cout << "The Guardian has now " << monsters.monsterHealth << " hp left" << endl;

            if (monsters.monsterHealth == 0)
            {
                cout << "You killed the Temple Guardian!";
                gainExperience(character, 200);
                result.lostBattle = false;
                break;
            }

            system("pause");
            cout << "\nThe Guardian did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " hp left" << endl;

            if (character.health_points <= 0)
            {
                cout << "You lost the battle!";
                cout << "-> Exiting to main menu...";
                cin.get();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                result.lostBattle = true;
                break;
            }

            break;
        }
        case 2:
        {
            monsters.monsterDamage = ((rand() % 10) + 1);

            if (character.class_type == "Barbarian")
            {
                monsters.monsterDamage += 20;
            }
            else if (character.class_type == "Outlaw")
            {
                monsters.monsterDamage += 10;
            }

            if (monsters.monsterDamage >= character.health_points)
            {
                character.health_points = 0;
            }
            else
            {
                character.health_points -= monsters.monsterDamage;
            }
            cout << "In a result of defence, Guardian did " << monsters.monsterDamage << " damage to you" << endl;
            cout << "You are left with " << character.health_points << " HP" << endl;
            break;
        }
        case 3:
        {
            char quitchoice;
            cout << "Are you sure you want to exit? (Y/n): ";
            cin >> quitchoice;
            if (quitchoice == 'Y' || quitchoice == 'y')
            {
                result.exitQuest = true;
                break;
            }
            break;
        }
        default:
        {
            cout << "Invalid Option. Try again!";
            break;
        }
        }

    } while (monsters.monsterHealth > 0 && character.health_points > 0);
    result.exitQuest = false;
    return result;

}
bool puzzle_3(Hero& character)
{
    system("cls");
    bool orbsPlaced[3] = { false, false, false }; // orbs placed (using bool)
    bool pedestalsOccupied[3] = { false , false, false };
    bool puzzleCompleted;
    cout << "Balance is the key to unlocking the path." << endl;

    while (!(orbsPlaced[0] && orbsPlaced[1] && orbsPlaced[2] && pedestalsOccupied[0] && pedestalsOccupied[1] && pedestalsOccupied[2])) // loop will run until orbs are not placed
    {

        cout << "Chamber Status:" << endl;
        for (int i = 0; i < 3; i++)
        {
            cout << (orbsPlaced[i] ? "O" : " ") << " ";
        }
        cout << endl;

        for (int i = 0; i < 3; i++)
        {
            cout << (pedestalsOccupied[i] ? "P" : " ") << " ";
        }
        cout << endl;


        int orbIndex, pedestalIndex;
        cout << "Choose an orb (1-3) and a pedestal (1-3) to place it on: ";
        cin >> orbIndex >> pedestalIndex;


        if (orbIndex < 1 || orbIndex > 3 || pedestalIndex < 1 || pedestalIndex > 3)
        {
            cout << "Invalid input. Try again." << endl;
            continue;
        }

        orbIndex--;
        pedestalIndex--;


        if (pedestalsOccupied[pedestalIndex])
        {
            cout << "Pedestal already occupied. Try again." << endl;
            continue;
        }


        pedestalsOccupied[pedestalIndex] = true;

        if (orbIndex != pedestalIndex)
        {
            cout << "Imbalance detected. Resetting puzzle." << endl;

            for (int i = 0; i < 3; ++i)
            {
                orbsPlaced[i] = false;
                pedestalsOccupied[i] = false;
            }
        }
        else
        {

            orbsPlaced[orbIndex] = true;
        }
    }

    cout << "Congratulations! The puzzle is solved. The path forward is revealed." << endl;
    return true;
}

