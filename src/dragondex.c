/* Taylor Veith
 * COP3223
 * dragondex.c
 * 11/19/2014
 *
 * All options implemented: adding, removing, searching, and listing dragons
 *
 * Loads in team information from library.txt and processes information
 */

//included libraries
#include <stdio.h>

//constants
#define MAX_LENGTH 40
#define MAX_TEAM 100

//define structures given in assignment sheet
typedef struct dragon {
    char name[MAX_LENGTH];
    char color[MAX_LENGTH];
} Dragon;

typedef struct collection {
    struct dragon team[MAX_TEAM];
    int num_dragons;
} Collection;

//function prototypes
int is_command(const char *command_string);
int add_dragon(Collection *dragon_collection, const char *name, const char *color);
int remove_dragon(Collection *dragon_collection, const char *name, Dragon *removed_dragon);
int search_dragon(const Collection *dragon_collection, const char *name);
int list_dragon(const Collection *dragon_collection, const char *color, Collection *dragon_results);

//main function
int main() {
    //variable declaration
    int number_of_instructions;

    //create a Collection to hold your dragon team and a pointer to it
    Collection dragon_collection;
    Collection *dragon_collection_ptr = &dragon_collection;
    dragon_collection.num_dragons = 0;

    //open dragon.txt
    FILE *ifp = fopen("dragon.txt", "r");

    //scan first line from dragon.txt, the number of instructions
    fscanf(ifp, "%d", &number_of_instructions);

    //iterate over each instruction
    size_t i;
    for(i = 0; i < number_of_instructions; ++i) {
        //declare variables local to the loop
        //status will be a general variable to store our returned values
        int status;
        char command_string[MAX_LENGTH];
        char dragon_name[MAX_LENGTH];
        char dragon_color[MAX_LENGTH];

        fscanf(ifp, "%s", command_string);

        //determine what the command is and process it
        switch(is_command(command_string)) {
            case 0: // not a command
                printf("input file not formatted correctly. expected command, got: %s\n", command_string);
                break;
            case 1: // add
                //read in the two parameters given with an add instruction - name, and color
                fscanf(ifp, "%s", dragon_name);
                fscanf(ifp, "%s", dragon_color);

                //add the dragon to the dragon collection
                status = add_dragon(dragon_collection_ptr, dragon_name, dragon_color);

                //interpret the result
                if(status) {
                    printf("Error adding %s the %s dragon. Too many dragons.\n", dragon_name, dragon_color);
                } else {
                    printf("%s the %s dragon has been added to the team.\n", dragon_name, dragon_color);
                }
                break;
            case 2: // remove
                //read in the name parameter
                fscanf(ifp, "%s", dragon_name);

                //create a temporary Dragon to store the dragon we've removed, as we need the name and color later
                Dragon removed_dragon;

                //remove the dragon
                status = remove_dragon(dragon_collection_ptr, dragon_name, &removed_dragon);

                //interpret results
                if(status) {
                    printf("%s the dragon was not found in your team.\n", dragon_name);
                } else {
                    printf("%s the %s dragon has been removed from the team.\n", removed_dragon.name, removed_dragon.color);
                }
                break;
            case 3: // search
                //read in the dragon name parameter
                fscanf(ifp, "%s", dragon_name);

                //search for the dragon and return the first result
                status = search_dragon(dragon_collection_ptr, dragon_name);

                //interpret results
                if(status != -1) {
                    Dragon temp_dragon = (*dragon_collection_ptr).team[status];
                    printf("%s the dragon is currently on the team.\n", temp_dragon.name);
                } else {
                    printf("%s the dragon is NOT currently on the team.\n", dragon_name);
                }
                break;
            case 4: // list
                //we'll search by color, so read in the dragons color
                fscanf(ifp, "%s", dragon_color);

                //create a Collection to store the results in
                Collection dragon_results;
                dragon_results.num_dragons = 0;

                //pass our results structure and fill it with results
                status = list_dragon(dragon_collection_ptr, dragon_color, &dragon_results);

                //interpret those results
                if(status) {
                    printf("%s dragons:\n", dragon_color);
                } else {
                    printf("%s dragons:\n", dragon_color);
                    Dragon temp_dragon;
                    size_t j;
                    for(j = 0; j < dragon_results.num_dragons; ++j) {
                        temp_dragon = dragon_results.team[j];
                        printf("%s", temp_dragon.name);
                        printf("\n");
                    }
                }
                break;
        }
        printf("\n");
    }
    printf("\n");

    //close the read-only file so TA doesn't get angry
    fclose(ifp);
    return 0;
}

/**
 * Returns an integer representing the command, if any, we've read in
 * Returns 0 if the string read in is not a command
 *
 * @param command_string     the unprocessed string read in
 * @return int, 0 if not a command or 1-4 otherwise, representing the
 *         four possible commands
 */
int is_command(const char *command_string) {
    //declare and initialize command_int to 0 to
    int command_int = 0;

    //compare the passed string to known names
    //of commands, and if a match is made, set
    //command_int to the respective value
    if(!strcmp(command_string, "ADD")) {
        command_int = 1;
    } else if(!strcmp(command_string, "REMOVE")) {
        command_int = 2;
    } else if(!strcmp(command_string, "SEARCH")) {
        command_int = 3;
    } else if(!strcmp(command_string, "LIST")) {
        command_int = 4;
    }

    //return 0, or if a command was found, its
    //respective value
    return command_int;
}

/**
 * Adds the given dragon to the collection structure
 *
 * @param dragon_collection  structure of type Collection
 * @param name               string containing the name of the dragon
 * @param color              string containing the color of the dragon
 * @return int, 0 if add succeeded, 1 for failure
 */
int add_dragon(Collection *dragon_collection, const char *name, const char *color) {
    //store size rather than constantly dereferencing the pointer
    int num_dragons = (*dragon_collection).num_dragons;

    //if the number of dragons already meets or exceeds MAX_TEAM,
    //return 1 to represent an error as the dragon was not added
    if(num_dragons >= MAX_TEAM) {
        return 1;
    }

    //otherwise, copy the passed name and color into the respective
    //dragon structure
    strcpy((*dragon_collection).team[num_dragons].name, name);
    strcpy((*dragon_collection).team[num_dragons].color, color);

    //a dragon was added, so increase the dragon count
    ++(*dragon_collection).num_dragons;

    //if we've reached this point, assume operation succeeded
    return 0;
}

/**
 * Removes the given dragon from passed collection structure and places
 * it in the passed Dragon structure for later use
 *
 * @param dragon_collection  structure of type Collection
 * @param name               string containing the name of the dragon
 * @param removed_dragon     structure of type Dragon
 * @return int, 0 if remove succeeded, 1 for failure
 */
int remove_dragon(Collection *dragon_collection, const char *name, Dragon *removed_dragon) {
    //declare status and initialize to 1, representing an error
    int status = 1;
    //store size rather than constantly dereferencing the pointer
    int num_dragons = (*dragon_collection).num_dragons;

    //iterate over each dragon in the collection, and if a match
    //is found to the passed name, "remove" it by overwriting it
    //with the last dragon in the collection. Then mark the last
    //dragons slot in the array as free space by decrementing
    //num_dragons
    size_t i;
    for(i = 0; i < num_dragons; ++i) {
        //compare passed name to names in team
        if(!strcmp((*dragon_collection).team[i].name, name)) {
            //we'll need the removed dragon later, so save it
            *removed_dragon = (*dragon_collection).team[i];

            //move the last dragon in the team to the slot of
            //the dragon we're removing, essentially overwriting
            //it.
            (*dragon_collection).team[i] = (*dragon_collection).team[num_dragons - 1];

            //finally, decrement the dragon count, rendering the
            //last slot in our team "empty" so it can be overwritten.
            --(*dragon_collection).num_dragons;

            //we has results, make status 0
            status = 0;
            break;
        }
    }

    //finally, return the status. 1 if error, 0 if success
    return status;
}

/**
 * Traverses the passed collection structure searching for dragon
 * with the given name. Returns its position in the array if it
 * exists, or -1 if not found
 *
 * @param dragon_collection  structure of type collection
 * @param name               string containing exact name of dragon
 * @return int, -1 if no dragon is found or if found, the number
 *         representing the dragons location in the collection
 */
int search_dragon(const Collection *dragon_collection, const char *name) {
    //declare position and initialize to -1, representing no result
    int element = -1;

    //iterate over each dragon in the collection, and if a match
    //is found, note the position in the array and stop the loop
    size_t i;
    for(i = 0; i < (*dragon_collection).num_dragons; ++i) {
        //compare passed name to names in team
        if(!strcmp((*dragon_collection).team[i].name, name)) {
            //if found, store the element and break.
            element = i;
            break;
        }
    }

    //return the position
    return element;
}

/**
 * Traverses the passed structure of type dragon_collection and prints
 * dragon information that match the passed color
 *
 * @param dragon_collection  structure of type Collection
 * @param name               string containing exact name of dragon
 * @param dragon_results     structure of type Collection
 * @return int, -1 if no dragon is found or if found, the number
 *         representing the dragons location in the collection
 */
int list_dragon(const Collection *dragon_collection, const char *color, Collection *dragon_results) {
    //declare status and initialize to 1, representing an error
    int status = 1;

    //iterate over each dragon in the collection, and if a match
    //is found to the passed name, "remove" it by overwriting it
    //with the last dragon in the collection. Then mark the last
    //dragons slot in the array as free space by decrementing
    //num_dragons
    size_t i;
    for(i = 0; i < (*dragon_collection).num_dragons; ++i) {
        //compare passed color to colors in team
        if(!strcmp((*dragon_collection).team[i].color, color)) {
            //if match, add dragon to results team
            (*dragon_results).team[(*dragon_results).num_dragons] = (*dragon_collection).team[i];

            //increment number of dragons in results team
            ++(*dragon_results).num_dragons;
            status = 0;
        }
    }

    //finally, return the status. 1 if error, 0 if success
    return status;
}
