# simpleStack
Simple stack realization, according to c++11 standard.


Here you mentioned about an issue regarding code style about dividing long lines of code to few short lines . 

Example:
std::string s = "statement1" + "statement2" + "statement3" + "statement4";

In order to make it more indented and short , I suugest , you store the statements as

std::string s1 = "statement1" , s2 = "statement2" , s3 = "statement3" , s4 = "statement4" ;

std::s5 = s1 + s2 + s3 + s4 ; 
