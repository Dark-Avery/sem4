#include <iostream>
#include <string>
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <vector>
#include <stack>
#include <algorithm>
 
using namespace std;
 
enum type_of_lex {
    LEX_NULL,                                                           
	LEX_AND, LEX_BOOL, LEX_STRING, LEX_DO, LEX_ELSE, LEX_IF,            
	LEX_FALSE, LEX_INT, LEX_NOT, LEX_OR, LEX_PROGRAM, LEX_READ ,        
	LEX_TRUE, LEX_WHILE, LEX_WRITE, LEX_GOTO, LEX_BREAK, LEX_FOR,                                                 
	LEX_FIN,                                                            
	LEX_SEMICOLON, LEX_DOG, LEX_COMMA, LEX_COLON, LEX_ASSIGN, LEX_OPPAR,
	LEX_CLPAR, LEX_EQ, LEX_L, LEX_G, LEX_PLUS, LEX_MINUS, LEX_MULT,     
	LEX_DIV, LEX_LEQ, LEX_NEQ, LEX_GEQ, LEX_DQM, LEX_FIGOP, LEX_FIGCL,  
	LEX_STRINGCONST, LEX_NUM, LEX_ID, LEX_UNMIN,     
    POLIZ_LABEL,
	POLIZ_ADDRESS,
	POLIZ_GO, 
	POLIZ_FGO                              
};
 
////////////////////////////////////////////////////////////////////////////////////////////

class Lex {
    type_of_lex   t_lex;
    int           v_lex;
public:
    Lex ( type_of_lex t = LEX_NULL, int v = 0 ): t_lex (t), v_lex (v)  { }
    type_of_lex  get_type () const { 
    	  return t_lex; 
    }
    int get_value () const { 
    	  return v_lex; 
    }
    friend ostream & operator<< ( ostream &s, Lex l );
};

////////////////////////////////////////////////////////////////////////////////////////////
 
class Ident {
    string      name;
    bool        declare;
    type_of_lex type;
    bool        assign;
    bool        label = false;
    int         label_str_num;
    int         value_int;
public:
    Ident() { 
        declare = false; 
        assign  = false; 
    }
    bool operator== ( const string& s ) const { 
        return name == s; 
    }
    Ident ( const string n ) {
        name    = n;
        declare = false; 
        assign  = false;
    }
    string get_name () const { 
        return name; 
    }
    bool get_declare () const { 
        return declare; 
    }
    void put_declare () { 
        declare = true; 
    }
    type_of_lex get_type () const { 
        return type; 
    }
    void put_type ( type_of_lex t ) { 
        type = t; 
    }
    bool get_assign () const { 
        return assign; 
    }
    void put_assign () { 
        assign = true; 
    }
    int get_label_str_num() {
        return label_str_num;
    }
    void put_label_str_num(int c) {
        label_str_num = c;
    }
    int  get_value_int () const { 
        return value_int; 
    }
    void put_value_int ( int v ) { 
        value_int = v; 
    }
    bool get_label() {
        return label;
    }
    void put_label() {
        label = true;
    }
    vector <int> label_gotos;
};
 
vector<Ident> TID;
 
int put ( const string & buf ) {
    vector<Ident>::iterator k;
    if (( k = find ( TID.begin (), TID.end (), buf )) != TID.end () )
        return k - TID.begin();
    TID.push_back ( Ident(buf) );
    return TID.size () - 1;
}
 
////////////////////////////////////////////////////////////////////////////////////////////

int isalpha (char c) {
    char alphabet [26] = {'a','b','c','d','e','f','g','h','i',
                          'j','k','l','m','n','o','p','q','r',
                          's','t','u','v','w','x','y','z'};
    for (int i = 0; i<26; i++) {
        if (c == alphabet[i]) {
            return 1;
        }
    }
    return 0;
}

int isdigit (char c) {
    char digits[10] = {'0','1','2','3','4','5','6','7','8','9'};
    for (int i = 0; i<10; i++) {
        if (c == digits[i]) {
            return 1;
        }
    }
    return 0;  
}

int str_numb = 1, position_numb = 1;
vector<string> STR;

int add (const string & buf) {
    vector <string>::iterator k;
    if ( (k = find (STR.begin(), STR.end(), buf)) != STR.end() ) {
        return k - STR.begin();
    }
    STR.push_back (buf);
    return STR.size() - 1;
}

////////////////////////////////////////////////////////////////////////////////////////////

class Scanner {
    FILE * fp;
    char   c;
    int look ( const string buf, const char ** list ) {
        int i = 0;
        while ( list[i] ) {
            if ( buf == list[i] )
                return i;
            ++i;
        }
        return 0;
    }
    void gc () {
        c = fgetc (fp);
    }
public:
    static const char * TW [], * TD [];
    Scanner ( const char * program ) {
        if ( !(fp = fopen ( program, "r" )) ) 
            throw  "can't open file" ;
    }
    Lex get_lex ();
};
 
const char *
Scanner::TW    [] = { "", "and", "bool", "string", "do", "else", "if", "false", "int", "not", "or", "program",
                    "read", "true", "while", "write", "goto", "break", "for", NULL };
 
const char *
Scanner::TD    [] = { "", ";", "@", ",", ":", "=", "(", ")", "==", "<", ">", "+", "-", "*", "/", "<=", "!=", ">=", 
                    "\"", "{", "}", NULL };
 
Lex Scanner::get_lex () {
    enum    state { H, IDENT, NUMB, ALE, NEQ, STRING, COM_BEG, COM_END, COM, COM_WRONG, COMSL };
    int     d, j;
    string  buf, s;
    state   CS = H;
    for(;;) {
        gc ();
        position_numb++;
        switch ( CS ) {
            case H:
                if ( c==' ' || c == '\n' || c== '\r' || c == '\t' ) {
                    if (c == '\n') {
                        str_numb++;
                        position_numb = 1;
                    }
                }
                else if ( isalpha (c) ) {
                    buf.push_back (c);
                    CS  = IDENT;
                }
                else if ( isdigit (c) ) {
                    d   = c - '0';
                    CS  = NUMB;
                } 
                else if ( c == '\"') {
                    CS = STRING;
                }
                else if ( c == '/' ) {
                    CS  = COM_BEG;
                }
                else if (c == '*') {
                    CS = COM_WRONG;
                }
                else if ( c == '=' || c == '<' || c == '>' ) { 
                    buf.push_back (c);
                    CS  = ALE; 
                }
                else if (c == '@')
                    return Lex ( LEX_FIN );
                else if (c == '!') {
                    buf.push_back (c);
                    CS  = NEQ;
                }
                else {
                    buf.push_back (c);
                    if ( ( j = look ( buf, TD) ) ){
                        return Lex ( (type_of_lex)( j + (int) LEX_FIN ), j );
                    }
                    else
                        throw c;
                }
                break;
            case IDENT:
                if ( isalpha (c) || isdigit (c) ) {
                    buf.push_back (c); 
                }
                else {
                    ungetc ( c, fp );
                    if ( (j = look ( buf, TW) ) ) {
                        return Lex ( (type_of_lex) j, j );
                        }
                    else {
                        j = put ( buf );
                        return Lex ( LEX_ID, j );
                    }
                }
                break;
            case NUMB:
                if ( isdigit (c) ) {
                    d = d * 10 + ( c - '0' );
                }
                else if (isalpha (c)) {
                    throw c;
                }
                else {
                    ungetc ( c, fp );
                    return Lex ( LEX_NUM, d );
                }
                break;
            case STRING:
                if ((c != '\"') && (c != '@')) {
                    buf.push_back(c);
                }
                else if (c == '@') {
                    throw c;
                }
                else {
                    j = add(buf); 
                    return Lex (LEX_STRINGCONST, j);
                }
                break;
            case COM_BEG:
                if ( c == '*' ) {
                    CS = COM;
                } 
                else if ( c == '/') {
                    CS = COMSL;
                }
                else {
                    ungetc(c, fp);
                    j = look("/", TD); 
                    return Lex((type_of_lex) (j+(int) LEX_FIN),j);
                } 
                break;
            case COMSL:
                if ( c == '\n') {
                    CS = H;
                }
                else if (c == '@') {
                    throw c;
                }
                break;
            case COM:
                if ( c == '*' ) {
                    CS = COM_END; 
                }
                else if (c == '@') {
                    throw c;
                }
                break;
            case COM_END:
                if ( c == '/' ) {
                    CS = H; 
                }
                else {
                    ungetc(c, fp); 
                    CS = COM;
                }
                break;
            case COM_WRONG:
                if ( c == '/' ) {
                    throw c; 
                }
                else {
                    ungetc(c, fp);
                    j = look("*", TD); 
                    return Lex((type_of_lex) (j+(int) LEX_FIN),j);
                } 
                break;
            case ALE:
                if ( c == '=' ) {
                    buf.push_back ( c );
                    j = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_FIN ), j );
                }
                else {
                    ungetc ( c, fp );
                    j = look ( buf, TD );
                    return Lex ( (type_of_lex) ( j + (int) LEX_FIN ), j );
                }
                break;
            case NEQ:
                if ( c == '=' ) {
                    buf.push_back(c);
                    j   = look ( buf, TD );
                    return Lex ( LEX_NEQ, j );
                }
                else
                    throw '!';
                break;
        }
    }
}

ostream & operator<< ( ostream &s, Lex l ) {
    string t;
    if ( l.t_lex <= LEX_FOR )
        t = Scanner::TW[l.t_lex];
    else if ( l.t_lex >= LEX_FIN && l.t_lex < LEX_STRINGCONST )
        t = Scanner::TD[ l.t_lex - LEX_FIN ];
    else if ( l.t_lex == LEX_STRINGCONST )
        t = "STRCONST";
    else if ( l.t_lex == LEX_NUM )
        t = "NUMB";
    else if ( l.t_lex == LEX_ID )
        t = TID[l.v_lex].get_name ();
    else if ( l.t_lex == LEX_UNMIN )
        t = "$-";
    else if ( l.t_lex == POLIZ_LABEL )
        t = "Label";
    else if ( l.t_lex == POLIZ_ADDRESS )
        t = TID[l.v_lex].get_name ();
        // t = "Addr";
    else if ( l.t_lex == POLIZ_GO )
        t = "!";
    else if ( l.t_lex == POLIZ_FGO ) 
        t = "!F";
    else 
        throw l;
    s << '(' << t << ',' << l.v_lex << ");" << endl;
    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////

template <class T, int max_size > 
class Stack
{
    T s[max_size];
    int top;
public:
    Stack() {
        top = 0;
    }
    void reset() {
        top = 0;
    }
    bool is_empty() {
        return top == 0;
    }
    bool is_full() {
        return top == max_size;
    }
    void push(T i) {
        if ( !is_full() )
            s[top++] = i;
        else
            throw "Stack_is_full";

    }
    T pop() {
        if ( !is_empty() )
            return s[--top];
        else
            throw "Stack_is_empty";
    }
};

////////////////////////////////////////////////////////////////////////////////////////////

type_of_lex z;

vector <int> label_vect;

void search(int tid_num) {
    for (int i = 0; i < label_vect.size(); i++) {
        if (label_vect[i] == tid_num) {
            label_vect.erase (label_vect.begin() + i);
            i--;
        }
    }
}

struct Br {
    int break_from;
    bool break_on = false;
};

////////////////////////////////////////////////////////////////////////////////////////////

class Parser {
    Lex curr_lex;
    type_of_lex c_type;
    int c_val;
    int in_loop = 0;
    int in_for = 0;
    vector<Br> breaks;
    Scanner scan;
    Stack <int, 100> st_int;
    Stack <type_of_lex, 100> st_lex;
    void PR(); 
    void D1(); 
    void OP1();
    void VAR(); 
    void OP();
    void ST(); 
    void E1(); 
    void T(); 
    void F();
    
    void dec (type_of_lex type); // семантичиеские действия
    void check_id ();
    void check_op ();
    void check_not ();
    void check_unminus();
    void eq_type ();
    void eq_bool ();
    void check_id_in_read ();
    void set_adress(int c_val);
    void gl() {
        curr_lex = scan.get_lex();
        c_type = curr_lex.get_type();
        c_val = curr_lex.get_value();
    }
public:
    vector <Lex> poliz;
    Parser (const char *program): scan (program) {}
    void analyze();
};

////////////////////////////////////////////////////////////////////////////////////////////

void Parser::PR() {
    if (c_type == LEX_PROGRAM) { gl();}
    else {throw "ERROR: NO KEYWORD \"program\" !";}
    if (c_type == LEX_FIGOP) {gl();}
    else {throw "ERROR: NO \"{\" AFTER \"program\" !";}
    D1();
    OP1();
    if (c_type == LEX_FIGCL) {gl();}
    else {throw "ERROR: NO \"}\" AFTER \"program\" !";}
}

void Parser::D1() {
    while ((c_type == LEX_INT) || (c_type == LEX_STRING || c_type == LEX_BOOL)) {
        z = c_type;
        st_int.reset();
        gl();
        VAR();
        while (c_type == LEX_COMMA){ gl(); VAR();}
        if (c_type != LEX_SEMICOLON){ throw "ERROR: NO \";\" AFTER VARIABLE DECLARATION!";}
        dec(z);
        gl();
    }

}

void Parser::VAR() {
    int c_val0 = c_val;
    Lex curr_lex2;
    if (c_type==LEX_ID){st_int.push(c_val);gl();}
    else {throw "ERROR: DECLARATION OF NON-VARIABLE!";}
    if (c_type == LEX_ASSIGN) {
        gl();
        curr_lex2 = curr_lex;
        if ((c_type == LEX_NUM)||(c_type == LEX_STRINGCONST) ||
            c_type == LEX_TRUE || c_type == LEX_FALSE) {
                if ((z == LEX_INT) && (c_type != LEX_NUM)) {
                    throw "ERROR: ASSIGNING WRONG CONST TYPE!";
                }
                else if ((z == LEX_STRING) && (c_type != LEX_STRINGCONST)) {
                    throw "ERROR: ASSIGNING WRONG CONST TYPE!";
                }
                else if ((z == LEX_BOOL) && (c_type != LEX_TRUE) &&
                        (c_type != LEX_FALSE)) {
                    throw "ERROR: ASSIGNING WRONG CONST TYPE!";
                }
                else {
                    poliz.push_back(Lex(POLIZ_ADDRESS, c_val0));
                    poliz.push_back(curr_lex2);
                    poliz.push_back(Lex(LEX_ASSIGN));
                    gl();
                }
        }
        else {throw "ERROR: ASSIGNING NON CONST VALUE IN VARIABLE DECLARATION!";}
    }
}

void Parser::OP1() {
    if (c_type != LEX_FIGCL)
        OP();
    while ((c_type != LEX_FIN) && (c_type != LEX_FIGCL)) { OP();}
    if (c_type == LEX_FIN) {throw "ERROR: SYNTAX ERROR!";}
}

void Parser::OP() {
    if (c_type == LEX_ID) {
        if (TID[c_val].get_declare()) {
            check_id();
            poliz.push_back (Lex (POLIZ_ADDRESS, c_val));
            gl();
            if (c_type != LEX_ASSIGN) { throw "ERROR: SYNTAX ERROR WHILE ASSIGNING!";}
            gl();
            ST();
            eq_type();
            poliz.push_back (Lex (LEX_ASSIGN));
            if (c_type != LEX_SEMICOLON) { 
                if (c_type != LEX_CLPAR || !in_for)
                    throw "ERROR: NO \";\" AFTER ASSIGNING!";
            }
            if (!in_for)
                gl();
        }
        else {
            if (TID[c_val].get_label()) {
                throw "ERROR: LABEL HAS ALREADY BEEN DECLARED!";
            }
            TID[c_val].put_label();
            TID[c_val].put_label_str_num(poliz.size());
            search(c_val);
            set_adress(c_val);
            gl();
            if (c_type != LEX_COLON) { throw "ERROR: NO \":\" AFTER LABEL!";}
            gl();
            OP();
        }
    }
    else if (c_type == LEX_GOTO) { 
        gl();
        if (c_type != LEX_ID) {throw "ERROR: NO LABEL AFTER \"goto\"!";}
        if (TID[c_val].get_declare()){throw "ERROR: VARIABLE HAS ALREADY BEEN DECLARED!";}

        if (!TID[c_val].get_label()) {
            (TID[c_val].label_gotos).push_back(poliz.size());
            poliz.push_back (Lex ());
            label_vect.push_back(c_val);
        }
        else { poliz.push_back(Lex(POLIZ_LABEL, TID[c_val].get_label_str_num()));}
        poliz.push_back(Lex (POLIZ_GO));
        gl();
        if (c_type !=LEX_SEMICOLON) {throw "ERROR: NO \";\" AFTER \"goto\"!";}
        gl();
    }
    else if (c_type == LEX_IF) {
        int pl2,pl3;
        gl();
        if (c_type == LEX_OPPAR) { gl(); ST();eq_bool();}
        else {throw "ERROR: NO \"(\" AFTER \"if\"!";}

        pl2= poliz.size(); poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_FGO)); 

        if (c_type == LEX_CLPAR) { gl(); OP();}
        else {throw "ERROR: NO \")\" AFTER \"if\"!";}

        pl3 = poliz.size(); poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_GO));
        poliz[pl2] = Lex (POLIZ_LABEL, poliz.size( ));

        if (c_type == LEX_ELSE) { gl(); OP();}
        poliz[pl3] = Lex (POLIZ_LABEL, poliz.size( ));
    }
    else if (c_type == LEX_WHILE) {
        in_loop++;
        int pl0, pl1;

        pl0 = poliz.size();

        gl();
        if (c_type == LEX_OPPAR) { gl(); ST();eq_bool();}
        else {throw "ERROR: NO \"(\" AFTER \"while\"!";}
        
        pl1 = poliz.size( ); poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_FGO)); 

        if (c_type == LEX_CLPAR) { gl();}
        else {throw "ERROR: NO \")\" AFTER \"while\"!";}
        OP();

        poliz.push_back (Lex(POLIZ_LABEL, pl0));
        poliz.push_back (Lex (POLIZ_GO));
        poliz[pl1] = Lex (POLIZ_LABEL, poliz.size( ));
        in_loop--;
    }
    else if (c_type == LEX_FOR) {
        in_for++, in_loop++;
        int pl0, pl1, pl2, pl3;
        Br rr;
        breaks.push_back(rr);

        gl();
        if (c_type != LEX_OPPAR)
            throw "ERROR: NO \"(\" AFTER \"for\"!"; 
        gl();
        // if ((c_type == LEX_INT) || (c_type == LEX_STRING || c_type == LEX_BOOL))
        //     D1();
        // else
        if (c_type != LEX_SEMICOLON)
            OP();
        if (c_type != LEX_SEMICOLON)
            throw "ERROR: NO \";\" IN \"for\"!"; 

        pl0 = poliz.size();

        gl();
        if (c_type != LEX_SEMICOLON) {
            ST();
            eq_bool();
        }
        
        if (c_type != LEX_SEMICOLON)
            throw "ERROR: NO \";\" IN \"for\"!"; 

        pl1 = poliz.size( ); 
        poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_FGO)); 

        pl2 = poliz.size( ); 
        poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_GO)); 

        pl3 = poliz.size( );
        gl();
        if (c_type != LEX_CLPAR)
            OP();
        
        if (c_type != LEX_CLPAR)
            throw "ERROR: NO \")\" AFTER \"for\"!";

        poliz.push_back (Lex(POLIZ_LABEL, pl0));
        poliz.push_back (Lex (POLIZ_GO));

        poliz[pl2] = Lex (POLIZ_LABEL, poliz.size( ));
        gl();
        OP();
        // gl();

        poliz.push_back (Lex(POLIZ_LABEL, pl3));
        poliz.push_back (Lex (POLIZ_GO));

        poliz[pl1] = Lex (POLIZ_LABEL, poliz.size( ));

        rr = breaks.back();
        breaks.pop_back();
        // cout << rr.break_from << endl;
        if (rr.break_on) {
            
            poliz[rr.break_from] = Lex (POLIZ_LABEL, poliz.size( ));
            // break_on = false;
        }
        in_for--, in_loop--;
    }
    else if (c_type == LEX_BREAK) {
        if (!in_loop)
            throw "ERROR: \"break\" NOT IN CYCLE!";
        Br rr;
        rr = breaks.back();
        breaks.pop_back();
        rr.break_on = true;
        // cout << poliz.size() << endl;
        rr.break_from = poliz.size( );
        poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_GO)); 
        breaks.push_back(rr);
        gl();
        if (c_type != LEX_SEMICOLON) {throw "ERROR: NO \";\" AFTER \"break\"!"; }
        gl();
    }
    else if (c_type == LEX_DO) {
        in_loop = true;
        int pl0,pl1;

        pl0 = poliz.size();

        gl();
        OP();
        if (c_type != LEX_WHILE) {throw "ERROR: NO \"while\" AFTER \"do\"!";}
        gl();
        if (c_type == LEX_OPPAR) { gl(); ST();eq_bool();}
        else {throw "ERROR: NO \"(\" AFTER \"while\"!";}
        
        pl1 = poliz.size( ); poliz.push_back (Lex( ));
        poliz.push_back (Lex (POLIZ_FGO));
        poliz.push_back (Lex(POLIZ_LABEL, pl0));
        poliz.push_back (Lex (POLIZ_GO));
        poliz[pl1] = Lex (POLIZ_LABEL, poliz.size( ));

        if (c_type != LEX_CLPAR) {throw "ERROR: NO \")\" AFTER \"while\"!"; }
        gl();
        in_loop = false;
    }
    else if (c_type == LEX_READ) {
        gl();
        if (c_type == LEX_OPPAR) {
            gl();
            if (c_type != LEX_ID) {throw "ERROR: READING NON-VARIABLE!";}
            check_id_in_read();

            poliz.push_back (Lex (POLIZ_ADDRESS, c_val));

            gl();
        }
        else {throw "NO \"(\" AFTER \"read\"";}

        poliz.push_back (Lex (LEX_READ));

        if (c_type != LEX_CLPAR) {throw "ERROR: NO \")\" AFTER \"read\"!";}
        gl();
        if (c_type != LEX_SEMICOLON) {throw "ERROR: NO \";\" AFTER \"read\"!";}
        gl();
    }
    else if (c_type == LEX_WRITE) {
        gl();
        if (c_type == LEX_OPPAR) {
            gl();
            ST();
            poliz.push_back (Lex (LEX_WRITE));
        }
        else {throw "ERROR: NO \"(\" AFTER \"write\"!";}
        while (c_type == LEX_COMMA){ gl(); ST(); poliz.push_back (Lex (LEX_WRITE));}
        if (c_type != LEX_CLPAR) {throw "ERROR: NO \")\" AFTER \"while\"!";}
        gl();
        if (c_type != LEX_SEMICOLON) {throw "ERROR: NO \";\" AFTER \"while\"!";}
        gl();
    }
    else if (c_type == LEX_FIGOP) {
        gl();
        OP1();
        if (c_type != LEX_FIGCL) { throw "ERROR: NO \")\" AFTER OPERATOR!";}
        gl();
    }
    else {
        ST();
        if (c_type != LEX_SEMICOLON) { throw "ERROR: NO \";\" AFTER OPERATOR!";}
        gl();
    }
}

void Parser::ST() {
    E1();
    if ( c_type == LEX_EQ || c_type == LEX_L || c_type == LEX_G ||
         c_type == LEX_LEQ || c_type == LEX_GEQ || c_type == LEX_NEQ )
    {
        st_lex.push(c_type);
        gl();
        E1();
        check_op();
    }
}

void Parser::E1 () {
    T();
    while ( c_type==LEX_PLUS || c_type==LEX_MINUS || c_type==LEX_OR )
    {
        st_lex.push (c_type);
        gl();
        T();
        check_op();
    }
}

void Parser::T () {
    F();
    while ( c_type==LEX_MULT || c_type==LEX_DIV || c_type==LEX_AND )
    {
        st_lex.push (c_type);
        gl();
        F();
        check_op();
    }
}

void Parser::F () {
    if ( c_type == LEX_ID )
    {
        check_id();
        poliz.push_back (curr_lex);
        gl();
    }
    else
    if ( c_type == LEX_NUM )
    {
        st_lex.push ( LEX_INT );
        poliz.push_back (curr_lex);
        gl();
    }
    else
    if ( c_type == LEX_STRINGCONST )
    {
        st_lex.push ( LEX_STRING );
        poliz.push_back (curr_lex);
        gl();
    } 
    else
    if ( c_type == LEX_TRUE )
    {
        st_lex.push ( LEX_BOOL );
        poliz.push_back (curr_lex);
        gl();
    }
    else
    if ( c_type == LEX_FALSE )
    {
        st_lex.push ( LEX_BOOL );
        poliz.push_back (curr_lex);
        gl();
    }
    else
    if ( c_type == LEX_NOT )
    {
        gl();
        F();
        check_not();
    }
    else
    if ( c_type == LEX_MINUS )
    {
        gl();
        F();
        check_unminus();
    }
    else
    if ( c_type == LEX_OPPAR )
    {
        gl();
        ST();
        if ( c_type == LEX_CLPAR)
            gl();
        else
            throw "ERROR: NO \")\" AFTER STATEMENT!";
    }
    else
    if ( c_type == LEX_SEMICOLON )
    {
        if (!in_for)
            throw "ERROR: \";\" WITHOUT STATEMENT!";
    }
    else
    if ( c_type == LEX_CLPAR )
    {
        if (!in_for)
            throw "ERROR: NO \"(\"!";
    }
    else
        throw "ERROR: SYNTAX ERROR IN STATEMENT!";
}

////////////////////////////////////////////////////////////////////////////////////////////

void Parser::set_adress(int c_val) {
    int amount = (TID[c_val].label_gotos).size();
    for (int i = 0; i < amount; i++) {
        poliz[(TID[c_val].label_gotos)[i]] = Lex(POLIZ_LABEL, TID[c_val].get_label_str_num());
    }
}

void Parser::analyze() {
    gl();
    PR();
    if (!label_vect.empty()) {throw "ERROR: TRANSITION ON AN UNDECLARED LABEL!";}
    if (c_type != LEX_FIN) {
        cout << c_type << endl;
        throw "ERROR: NO END SIGN!";
    }
    int amount = poliz.size();
    for(int h = 0; h<amount; h++) {
        cout << h << " " << poliz[h];
    }
    cout << endl << "OK!" << endl;
}

void Parser::dec ( type_of_lex type ) {
    int i;
    while ( !st_int.is_empty())
    {
        i = st_int.pop();
        if ( TID[i].get_declare() )
            throw "ERROR: VARIABLE DECLARED TWICE!";
        else {
            TID[i].put_declare();
            TID[i].put_type(type);
        }
    }
}

void Parser::check_id() {
    if ( TID[c_val].get_declare() )
        st_lex.push(TID[c_val].get_type());
    else
        throw "ERROR: VARIABLE IN STATEMENT IS NOT DECLARED!";
}

void Parser::check_op () {
    type_of_lex t1, t2, op;
    t2 = st_lex.pop();
    op = st_lex.pop();
    t1 = st_lex.pop();
    if (t1!=t2) { throw "ERROR: WRONG TYPES IN OPERATION!"; }
    if ( op == LEX_PLUS || op == LEX_MINUS || op == LEX_MULT || op == LEX_DIV) {
        if (t1 == LEX_BOOL) {
            throw "ERROR: WRONG TYPES IN OPERATION!";
        }
        if (t1 == LEX_STRING) {
            if (op != LEX_PLUS) {
                throw "ERROR: WRONG TYPES IN OPERATION!";
            }
        }
        st_lex.push(t1);
    }
    else if (op == LEX_L || op == LEX_G || op == LEX_LEQ || op == LEX_GEQ ||
             op == LEX_EQ || op == LEX_NEQ) {
        if (t1 == LEX_BOOL) {
            throw "ERROR: WRONG TYPES IN OPERATION!";
        }
        if (t1 == LEX_STRING) {
            if (op != LEX_L && op != LEX_G && op != LEX_EQ && op != LEX_NEQ) {
                throw "ERROR: WRONG TYPES IN OPERATION!";
            }
        }
        st_lex.push(LEX_BOOL);
    }
    else {                         // AND, OR //
        if (t1 != LEX_BOOL) { 
            throw "ERROR: WRONG TYPES IN OPERATION!";
        }
        else {st_lex.push(LEX_BOOL);}
    }
    poliz.push_back(Lex(op));
}

void Parser::check_not () {
    if (st_lex.pop() != LEX_BOOL)
        throw "ERROR: WRONG TYPES IN OPERATION \"not\" !";
    else {
        st_lex.push (LEX_BOOL);
        poliz.push_back (Lex (LEX_NOT));
    }
}

void Parser::check_unminus () {
    if (st_lex.pop() != LEX_INT)
        throw "ERROR: WRONG TYPES IN OPERATION \"unar -\" !";
    else {
        st_lex.push (LEX_INT);
        poliz.push_back (Lex (LEX_UNMIN));
    }
}

void Parser::eq_type () {
    if ( st_lex.pop() != st_lex.pop() ) throw "ERROR: WRONG TYPES IN OPERATION \"=\" !";
}

void Parser::eq_bool () {
    if ( st_lex.pop() != LEX_BOOL )
        throw "ERROR: EXPRESSION IS NOT OF TYPE \"bool\" !";
}

void Parser::check_id_in_read () {
    if ( !TID [c_val].get_declare() )
        throw "ERROR: VARIABLE IN OPERATOR \"read\" IS NOT DECLARED";
}

////////////////////////////////////////////////////////////////////////////////////////////

template <class T, class T_EL>
void from_st (T& t, T_EL & x) { x = t.top(); t.pop(); }

class Executer {
public:
    void execute (vector <Lex> & poliz) {
        Lex pc_el;
        stack < Lex > args;
        Lex i, j; int index = 0, size = poliz.size ( );
        int val;
        int k;
        string val_str;
        while ( index < size ) {
            pc_el = poliz [ index ];
            switch ( pc_el.get_type () ) {
                case LEX_NUM:
                    args.push(Lex(LEX_INT, pc_el.get_value()));
                    break;
                case POLIZ_ADDRESS: case POLIZ_LABEL: case LEX_STRINGCONST:
                    args.push ( poliz[index] );
                break;
                case LEX_TRUE:
                    args.push (Lex(LEX_BOOL, 1));
                    break;
                case LEX_FALSE:
                    args.push (Lex(LEX_BOOL, 0));
                    break;
                case LEX_ID:
                    val = pc_el.get_value ( );
                    if ( TID [ val ].get_assign ( ) ) {
                        if ( TID [ val ].get_type ( ) == LEX_STRING ) {
                            args.push(Lex(LEX_STRINGCONST,TID[val].get_value_int() )); break;
                        }
                        else if ( TID [ val ].get_type ( ) == LEX_INT ) {
                            args.push(Lex(LEX_INT,TID[val].get_value_int() )); break;
                        }
                        else {
                            args.push(Lex(LEX_BOOL,TID[val].get_value_int() )); break;
                        }
                    }
                    else
                        throw "POLIZ: indefinite identifier";

                case LEX_NOT:
                    from_st(args, i);
                    args.push(Lex(LEX_BOOL, !(i.get_value()))); break;
                case LEX_UNMIN:
                    from_st(args, i);
                    args.push(Lex(LEX_INT, (-1)*i.get_value())); break;
                case LEX_OR:
                    from_st(args,j);
                    from_st(args,i);
                    args.push(Lex(LEX_BOOL, i.get_value() || j.get_value())); break;
                case LEX_AND:
                    from_st(args,j);
                    from_st(args,i);
                    args.push(Lex(LEX_BOOL, i.get_value() && j.get_value())); break;
                case POLIZ_GO:
                    from_st(args, i);
                    index = i.get_value() - 1; break;
                case POLIZ_FGO:
                    from_st(args, i);
                    from_st(args, j);
                    if( ! j.get_value()) index = i.get_value() -1; break;
                case LEX_WRITE:
                    from_st(args, i);
                    if (i.get_type() == LEX_INT ) {
                        cout <<i.get_value() << endl; break;
                    }
                    else if (i.get_type() == LEX_STRINGCONST) {
                        cout <<STR[i.get_value()] << endl; break;
                    }
                    else {
                        if (i.get_value() == 1) {cout << "TRUE" << endl;}
                        else {cout << "FALSE" << endl;}
                        break;
                    }
                case LEX_READ:
                    from_st (args, i);
                    if ( TID [ i.get_value() ].get_type () == LEX_INT ) {
                        cout << "Input int value for ";
                        cout << TID[i.get_value()].get_name () << " = "; 
                        cin >> k;
                    }
                    else if (TID [ i.get_value() ].get_type () == LEX_BOOL) { string j;
                            while(1) {
                                cout << "Input boolean value (TRUE or FALSE) for ";
                                cout << TID [i.get_value()].get_name ( ) << " = "; 
                                cin >> j;
                                if ( j != "true" && j != "false" ) {
                                    cout << "Error in input: true/false" << endl;
                                    continue;
                                }
                                k = (j == "true") ? 1 : 0; break;
                            }
                    }
                    else {
                        cout << "Input string value for ";
                        cout << TID [i.get_value()].get_name ( ) << " = ";
                        cin >> val_str;
                        k = add(val_str);
                    }
                    TID [ i.get_value() ].put_value_int (k);
                    TID [ i.get_value() ].put_assign ();
                    break;

                case LEX_PLUS:
                    from_st(args,j);
                    from_st(args,i);
                    if (i.get_type() == LEX_INT ) {
                        args.push(Lex(LEX_INT, i.get_value() + j.get_value())); break;
                    }
                    else {
                        val_str = STR[i.get_value()] + STR[j.get_value()];
                        k = add(val_str);
                        args.push(Lex(LEX_STRINGCONST, k)); break;
                    }
                case LEX_MULT:
                    from_st(args,j);
                    from_st(args,i);
                    args.push(Lex(LEX_INT, i.get_value() * j.get_value())); break;
                case LEX_MINUS:
                    from_st(args,j);
                    from_st(args,i);
                    args.push(Lex(LEX_INT, i.get_value() - j.get_value())); break;
                case LEX_DIV:
                    from_st(args,j);
                    from_st(args,i);
                    if(j.get_value() != 0) {
                        args.push(Lex(LEX_INT, i.get_value() / j.get_value())); break;
                    }
                    else throw "POLIZ:divide by zero";
                case LEX_EQ:
                    from_st(args,j);
                    from_st(args,i);
                    if (i.get_type() == LEX_INT ) {
                        args.push(Lex(LEX_BOOL, i.get_value() == j.get_value())); break;
                    }
                    else {
                        k = STR[i.get_value()] == STR[j.get_value()];
                        args.push(Lex(LEX_BOOL, k)); break;
                    }
                case LEX_GEQ:
                    from_st(args,j);
                    from_st(args,i);
                    args.push(Lex(LEX_INT, i.get_value() >= j.get_value())); break;
                case LEX_LEQ:
                    from_st(args,j);
                    from_st(args,i);
                    args.push(Lex(LEX_INT, i.get_value() <= j.get_value())); break;
                case LEX_G:
                    from_st(args,j);
                    from_st(args,i);
                    if (i.get_type() == LEX_INT ) {
                        args.push(Lex(LEX_BOOL, i.get_value()  > j.get_value())); break;
                    }
                    else {
                        k = STR[i.get_value()] > STR[j.get_value()];
                        args.push(Lex(LEX_BOOL, k)); break;
                    }
                case LEX_L:
                    from_st(args,j);
                    from_st(args,i);
                    if (i.get_type() == LEX_INT ) {
                        args.push(Lex(LEX_BOOL, i.get_value() < j.get_value())); break;
                    }
                    else {
                        k = STR[i.get_value()] < STR[j.get_value()];
                        args.push(Lex(LEX_BOOL, k)); break;
                    }
                case LEX_NEQ:
                    from_st(args,j);
                    from_st(args,i);
                    if (i.get_type() == LEX_INT ) {
                        args.push(Lex(LEX_BOOL, i.get_value() != j.get_value())); break;
                    }
                    else {
                        k = STR[i.get_value()] != STR[j.get_value()];
                        args.push(Lex(LEX_BOOL, k)); break;
                    }
                case LEX_ASSIGN:
                    from_st(args,j);
                    from_st(args,i);
                    TID[i.get_value()].put_value_int(j.get_value());
                    TID[i.get_value()].put_assign( ); break;
                case NULL:
                    throw "empty lexeme";
                default:
                    throw "POLIZ: unexpected elem";

            }
            index++;

        } 
        cout << "Finish of executing!!!" << endl;

    }
};

////////////////////////////////////////////////////////////////////////////////////////////

int main () {
    try {
        // Scanner S ( "prog.txt" );
        // Lex L = S.get_lex();
        // while (L.get_type() != LEX_FIN) {
        //     cout << L;
        //     L = S.get_lex();
        // }
        Parser pars ("prog.txt");
        pars.analyze();
        Executer exec;
        exec.execute(pars.poliz);

        return 0;
    }
    catch ( char c ) {
        cout << str_numb << ":" << position_numb << " unexpected symbol " << c << endl;
        return 1;
    }
    catch ( Lex l ) {
        cout << str_numb << ":" << position_numb << " unexpected lexeme " << l << endl;
        return 1;
    }
    catch (const char *s) {
        cout << str_numb << ":" << position_numb << " " << s << endl;}
    catch (...) {
        cout << "error 404" << endl;
        return 1;
    }
}