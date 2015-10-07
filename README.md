# Autocompleter-in-c
Autocomplete program in c using ternary search tree

This c program takes in a text file containing phrases in any language and asks the user to enter a prefix.

It then provides suggestions that closely match the provided prefix.

Note: The program reads 1000 lines at a time, as it expects a huge database file.
Should you want less than that as a developer, please modify the CHUNK argument in utils.h to a suitable factor, to 
avoid the possibility of crashes.

Upon invocation, you should then see messages like this:

Welcome to the autocomplete program

[INFO]: Loading database file containing list of phrases into memory ...

Reading "filenames follow"

[INFO]: Finished loading database file.

Please type the prefix of a word:

armou

Suggestions:

armour

armourcabbies

armourbearer

armourbearers

armourer

armourers

armoured

armourewd

armourd

armourdale

armour's

armourfit

armourflex

armourial

armouries

armouring

armourless

armourplating

armourplate

armourglass

armourglass

armours

armoury

armout

armouti

armouted

armouni

Please type the prefix of a word:

quit

No match found.

Cleaning up extra files ....

"filenames that are being deleted follow"

Cleanup done. Exiting the program.

Please press the ENTER key after entering the prefix to see suggestions in all cases.

Questions or comments can be directed to venkatesh201988@gmail.com
