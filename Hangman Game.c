// this module provides max_words secret words
// numbered 1...max_words

extern const int max_words;

// get_word(n) returns word #n
// requies: 1 <= n <= max_words
const char *get_word(int n);

const int max_strikes = 6;

const char *enter_game_number = 
  "Please enter a valid game number between 1 and %d.\n";

const char *invalid_game_number = 
  "Error, the number entered was not valid.\n";

const char *letter_prompt = 
  "Please enter a letter.\n";

const char *not_a_letter = 
  "The character %c is not a letter.\n";

const char *already_guessed_letter = 
  "You have already guessed the letter %c. Please enter another letter.\n";

const char *not_in_word = 
  "The letter %c is not in the word.\n";

const char *not_last_guess = 
  "Watch out! You only have %d more guesses left before your man is hung!\n";

const char *play_again = 
  "Do you want to play again? (Y for yes, N for no).\n";

const char *invalid_play_again_response = 
  "Error, invalid response.\n";

const char *game_over = 
  "Game over. The correct word was %s.\n";

const char *congratulations = 
  "You win! The correct word was %s.\n";

static char *hangman_ascii[7] = {
"\
0000000000000\n\
0           0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n",
"\
0000000000000\n\
0           0\n\
0           1\n\
0          1 1\n\
0           1\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n",
"\
0000000000000\n\
0           0\n\
0           1\n\
0          1 1\n\
0           1\n\
0           2\n\
0           2\n\
0           2\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n",
"\
0000000000000\n\
0           0\n\
0           1\n\
0          1 1\n\
0           1\n\
0          32\n\
0         3 2\n\
0        3  2\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n",
"\
0000000000000\n\
0           0\n\
0           1\n\
0          1 1\n\
0           1\n\
0          324\n\
0         3 2 4\n\
0        3  2  4\n\
0\n\
0\n\
0\n\
0\n\
0\n\
0\n",
"\
0000000000000\n\
0           0\n\
0           1\n\
0          1 1\n\
0           1\n\
0          324\n\
0         3 2 4\n\
0        3  2  4\n\
0          5\n\
0         5\n\
0        5\n\
0       5\n\
0\n\
0\n",
"\
0000000000000\n\
0           0\n\
0           1\n\
0          1 1\n\
0           1\n\
0          324\n\
0         3 2 4\n\
0        3  2  4\n\
0          5 6\n\
0         5   6\n\
0        5     6\n\
0       5       6\n\
0\n\
0\n" };


// print_hangman(strike) prints the hangman picture
//   for the given number of strikes
// requires: 0 <= strike <= max_strikes
void print_hangman(int strike) {
  assert(strike >= 0);
  assert(strike <= max_strikes);
  printf("%s", hangman_ascii[strike]);
}

bool is_letter(char c);

// change_cpy(b,d,c) updates the mutated version of the word c
// in b as a string to store the word in the state that it is printed
// that is by using appropriate asterisks and letters for characters
// that have already been guessed
// requires: b,c and d are not NULL
// efficiency: O(n)
void change_cpy(char b[], bool d[], char c[]) {
  int len=strlen(b);
  for (int i=0; i<len; ++i) {
    for (int j=0; j<128; ++j) {
      if (j==c[i]) {
        if (d[j]==true) {
          b[i]=c[i];
        }
      }
    }
  }
}

// mutate_first(g,h) creates the mutated copy of the word the moment
// the game starts, that is, all spaces are stores as spaces in g
// and all letters in h are stored as asterisks in g
// requires: g and h are not NULL
// efficiency: O(n)
void mutate_first(char g[],char h[]) {
  int len=strlen(h);
  for (int i=0; i<len; ++i) {
    if (h[i]==' ') {
      g[i]=' ';
    } else {
      g[i]='*';
    }
  }
}

// game_end(v) checks the mutated copy of the word
// stored in string as appropriate letters and asteisks to determine
// whether the game has ended or not. If all characters appear as
// letters and spaces and none appear as asterisks
// requires: v is not NULL
// efficiency: O(n)
bool game_end(char v[]) {
  int len=strlen(v);
  int end=false;
  for (int g=0; g<len; ++g) {
    if (is_letter(v[g])||
        (v[g]==' ')) {
      end=true;
    } else {
      return false;
    }
  }
  return end;
}

// print_begin(word) prints the initial state of the board
// that is, it consumes the word as a string 
// and prints spaces as spaces
// and all letters are printed as asterisks
// requires: word is not NULL
// efficiency: O(n)
void print_begin(char* word) {
  int lenw=strlen(word);
  for (int i=0; i<lenw; ++i) {
    if (word[i]==' ') {
      printf(" ");
    } else {
      printf("*");
    }
  }
  printf("\n");
}

// update_bool(a,b) takes in a boolean array a
// and a character b and updates the boolean array to
// record the existence of the character b at the position
// correspnding to the value of the character in the boolean array
// requires: a is not NULL, b is a valid character
// efficiency: O(1)
void update_bool(bool a[], char b) {
  for (int c=0; c<128; ++c) {
    if (c==b) {
      a[c]=true;
    }
  }
}

// new_board(c,word) takes in the boolean array c
// and the word and prints only those occurrences of
// the character that have alredy been guessed according to the
// state of the characters in the boolean array
// requires: c and word are not NULL
// time: O(n)
void new_board(bool c[], char* word) {
  int lenw=strlen(word);
  for (int i=0; i<lenw; ++i) {
    for (int j=0; j<128; ++j) {
      if (j==word[i]) {
        if (c[j]==true) {
          printf("%c",word[i]);
        } else if (word[i]==' ') {
          printf(" ");
        } else {
          printf("*");
        }
      }
    }
  }
  printf("\n");
}

// seen_so_far(a,b) takes in the boolean array and returns true
// if the character that have been just entered, b has already
// been guessed previously. Otherwise it returns false
// requires: a is not NULL
// time: O(1)
bool seen_so_far(bool a[], char b) {
  for (int i=0; i<128; ++i) {
    if (b==i) {
      if (a[i]==true) {
        return true;
      }
    }
  }
  return false;
}

// is_letter (c) takes in a character c and returns true
// if the consumed charcater is a letter and returns false 
// otherwsie
// time: O(1)
bool is_letter(char c) {
  if (('a'<=c)&&(c<='z')) {
    return true;
  } else if (('A'<=c)&&(c<='Z')) {
    return true;
  } else {
    return false;
  }
}

// in_word(d,e) takes in a word d and character e
// and returns true if the character e is present in the word d
// and returns false otherwise
// requires: d is not NULL
// time: O(n)
bool in_word(char d[], char e) {
  int len=strlen(d);
  for (int i=0; i<len; ++i) {
    if (d[i]==e) {
      return true;
    }
  }
  return false;
}

// gamehang() plays only one instance of the game hangman
// and exits the function if one instance of the game has been
// completed and it repeatedly asks the user for input if the user has
// entered an invalid number
// time: O(1)
void gamehang(void) {
  bool end=false;
  int a=0;
  while (1) {
  printf(enter_game_number,max_words);
  int c=scanf("%d",&a);
    if (c!=1) {
      break;
    } 
    if ((a<1)||(a>max_words)) {
    printf("%s",invalid_game_number);
  } else {
    char c[50]={0};
    strcpy(c,get_word(a));
    char mutcpy[50]={0};
    mutate_first(mutcpy,c);
    int strike=0;
      int numguess=0;
    bool d[128]={false};
    while (strike<max_strikes) {
      print_hangman(strike);
      printf("%s",letter_prompt);
      
      {if (numguess==0) {
        print_begin(c);
      } else {
        new_board(d,c);
      }
    }
      char e='a';
      int x=scanf(" %c",&e);
      if (x!=1) {
        break;
      }
      if (!(is_letter(e))) {
        printf(not_a_letter,e);
        ++numguess;
        continue;
      }
      if (('a'<=e)&&(e<='z')) {
        e=e-'a'+'A';
      }
      if (seen_so_far(d,e)) {
        printf(already_guessed_letter,e);
        ++numguess;
        continue;
      }
      if (!(seen_so_far(d,e))) {
      if (!(in_word(c,e))) {
        update_bool(d,e);
        printf(not_in_word,e);
        ++strike;
        if (strike<max_strikes) {
          printf(not_last_guess,(max_strikes-strike));
          continue;
        }
        if (strike==max_strikes) {
          print_hangman(max_strikes);
          printf(game_over,c);
          end=true;
          break;
        }
      }
        ++numguess;
      } if (!(seen_so_far(d,e))) {
        if (in_word(c,e)) {
          update_bool(d,e);
          change_cpy(mutcpy,d,c);
          if (game_end(mutcpy)) {
            printf(congratulations,c);
            end=true;
            break;
          } else {
           continue;
          }
        }
        ++numguess;
      }
    }
  }
    if (end==true) {
      break;
    }
  }
}

            
    
// main() plays several instance of the game until the user has
// entered N or n as the input. It plays several instances of
// the game as long as the user keeps on enetring Y or y as input.
// If the input is not either Y, y, N or n, then it send the
// message that it is invalid response
// time: O(y) where y is the number of times that game is played
int main(void) {
  while (1) {
  gamehang();
  char f='a';
  while (1) {
   printf("%s",play_again);
   int g=scanf(" %c",&f);
  if (g!=1) {
    break;
  } else {
    if ((f=='Y')||(f=='y')) {
      break;
    } else if ((f=='N')||(f=='n')) {
      break;
    } else {
      printf("%s",invalid_play_again_response);
      continue;
    }
  }
  }
    if ((f=='Y')||(f=='y')) {
      continue;
  } else {
      break;
}
}
}
