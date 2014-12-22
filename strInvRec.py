from sys import exit

def invert(string):
    
    length = len(string);
    if length == 1 or length == 0:
        return string;
    else:
        temp = string[0];
        string[0] = string[length - 1];
        string[length - 1] = temp;
        new_string = string[0:1] + invert(string[1:length - 1]) + string[length-1:];
        return new_string;

print "Reverse strings recursively, Enter quit to quit";

while 1:
    ip = raw_input("Enter String: ");

    if ip == "quit":
        exit();
    
    string = ip.split();
    string = invert(string);
    
    phrase = '';
    phrase += string[0];
    
    for j in string[1:]:
        phrase += ' ';
        phrase += j;
        
    print "Result: %s" % (phrase);
