**s$=Up Case$(s$)**
 
    Convert to uppercase
 
**s$=Lo Case$(s$)**
 
    Convert to lowercase
 
**s$=Flip Case$(s$)**

    swap upper and lowercase. 
 
**s$=Left Trim$(s$)**

    Trim spaces on left side

**s$=Left Trim$(s$,r$)**

    Remove any char in r$, from s$
    takes more then one char.

**s$=Right Trim$(s$)**

    Trim spaces on right side

**s$=Right Trim$(s$,r$)**

    Remove any char in r$, from s$ 
    takes more then one char.

**n=Bw Instr(txt$,item$)**

	Return first position.

**n=Bw Instr(txt$,item$,n)**

	Return first position, 
	limited by n number of chars.
 
**s$=Chr Conv$(s$,char1 To char2)**

	Replace char1 with char2 (ascii value)
 
**n=Str Count(txt$,item$)**
 
	Count the number of item$ in txt$

**n=Mem Str Count(n,s$)**

    So this one gives a illigal function call on AmosPro_Craft.lib,
    but there is no reason way it should not work.

    So in KittyCraft.library, it looks for the word until it finds memory address is 0 terminated.

**n=Mem Str Count([start] To [end],item$)**

    Find item$ in memory from [start] to [end].
 
**s$=Str Scramble$(s$,s$)**

    Makes a text string unreadable.
    (this command, do not use the original way to scramble the text)

**s$=Str Unscramble$(s$,s$)**
 
    Maes a scrambled text string readable.
    (this command, do not use the original way to unscramble the text)

**s$=Hex Dump$(address,n)**
    
    Dumps the first n bytes as hex, from Address.
    result stored in S$

**s$=Hex Dump$(address,len,bytes)**

    insert a space between x number of bytes, if bytes is 0, then no space is inserted.

    show hex dump in bytes

    *s$=Hex Dump$(address,len,1)*

    show hex dump in shorts    

    *s$=Hex Dump$(address,len,2)*

    show hex dump in ints32

    *s$=Hex Dump$(address,len,4)*

    show hex dump in int64

    *s$=Hex Dump$(address,len,8)*

**s$=Chr Dump$(n,n)**

    convert memory block to ascii string.
    0-31 and 128-159 converted to char 46
 
**s$=Str Peek$(address,len)**

    fetch string from address, len is length of the string in memory,

**s$=Str Peek$(address,len,term$)**

    fetch string from address, len is length of the string in memory, term$ is the end of string.

**Str Poke [address],s$**
 
    write string into [address]

**n=Chip Max Block**
 
    Get largest free block of chip ram

**n=Fast Max Block**

    Get largest free block of fast ram
 
**Mem Copy [StartAddress],[EndAddress] To [destAddress]**
 
    Copy all bytes from StartAddress, including EndAddress to DestAddress.

**n=Mem Type(n)**

    Get memory type, note this command will NOT 
    return the same memory types under AmigaOS4.1 as under AmigaOS3.1

**Mem Scramble [StartAddress] To [EndAddress],password$**

    Scamble memory from StartAddress, including EndAddress.
 
**Mem Scramble [bank],password$**

    Scamble the memory in the bank.

**Mem Unscramble [StartAddress] To [EndAddress],password$**
 
    Unscamble memory from StartAddress, including EndAddress.

**Mem Unscramble [bank],password$**

    Unscamble the memory in the bank.
 
s$=Dr File$(s$)
 
**s$=Dr Path$(path_and_name$)**

    Get path from string.
    if the file do not exists, 
    returns error 81 if does not exist.
 
n=Db Free(s$)
 
n=Db Used(s$)
 
n=Db Size(s$)
 
n=Disc State(s$)
 
s$=Disc Type$(s$)
 
n=File Protect(s$)

s$=File Comment$(s$)

n=File Length(s$)
 
n=File Type(s$)

Set Protect s$,n 
 
Set Comment s$,s$ 
 
**s$=Dr Name$(s$)**
 
    Set the current directory
	for command "Dr Next$".
	plase make sure read all files in the direcory 
	or use "Dr Forget" command, to undo 
	what this command has done.
	
    if the directory does not exists, 
	then this command will returns error 81.

	(this command can be used recursively, 
	every time you call this command, 
	it will stack up etch directory context.)
	
**s$=Dr Next$**

	Get the next file or dirctory.
	when your at the end of list you 
	get a empty string as return value.

	if you abort before reading all files, 
	you need to use "dr forget" command.
	If you do not use "dr forget", 
	you risk overflowing internal buffers.
 
**s$=Dr Comment$**

	This command should return file comment.
 
**n=Dr Protect**

	Return protection bits, 
	This command can only be used after a successful Dr Next$ command.
 
**n=Dr Length**

	Should return file length, 
	This command can only be used after a successful Dr Next$ command.

**n=Dr Type**

	Should return filesystem object type. (not sure if uses correct numbers)
 	This command can only be used after a successful Dr Next$ command.
 
n=Dr Fib  
 
**Dr Forget**

	This is used to forget about "Dr Name$" command,
	needs to be called, if you abort reading all files.
 
n=Disc Error  
 
Set Red n,n 
 
n=Pal Red(n)
 
Set Green n,n 
 
n=Pal Green(n)
 
Set Blue n,n 
 
n=Pal Blue(n)

Pal Spread n To n 
 
Pal Swap n,n 
 
Pal Copy n To n 
 
Reserve As Palette n,n 
 
n=Pal Count(n)
 
Pal To Bank n,n,n 
 
Pal To Bank n,n 
 
Pal To Bank n 
 
Pal From Bank n,n,n 
 
Pal From Bank n,n 
 
Pal From Bank n 
 
Pal Swap Bank n,n,n 
 
Pal Swap Bank n,n 
 
Pal Swap Bank n 
 
Set Bank Colour n,n,n,n 
 
n=Bank Colour(n,n,n)
 
Del Bank Colour n,n,n 
 
Tr Exec s$,n 
 
Tr Exec s$ 
 
n=Tr Error  
 
Tr Reset  
 
Tr Angle n 
 
n=Tr Get Angle  
 
Tr Left n 
 
Tr Right n 
 
Tr Towards n,n 
 
Tr Forward n 
 
Tr Forw n 
 
Tr Back n 
 
n=Tr Distance(n,n)
 
Tr Pen Up  
 
Tr Pen Down  
 
n=Tr Pen State  
 
Tr Move Rel n,n 
 
Tr Move n,n 
 
Tr Draw Rel n,n 
 
Tr Draw n,n 
 
n=Tr X Pos  
 
n=Tr Y Pos  
 
Tr Proportions n,n 
 
Tr Proportions n 
 
Tr Set Home n,n 
 
Tr Home  
 
n=Tr X Home  
 
n=Tr Y Home  
 
Tr Remember X  
 
Tr Remember Y  
 
Tr Remember A  
 
Tr Memorize X  
 
Tr Memorize Y  
 
Tr Memorize A  
 
n=Tr Base  
 
Fr Reset  

n=Fr X Position  
 
n=Fr Y Position  
 
Fr Position n,n 
 
n=Fr X Step  
 
n=Fr Y Step  
 
Fr Step n,n 
 
Fr Step n 
 
Fr Colour n,n 
 
n=Fr Get Colour(n)
 
Fr Window n,n,n,n,n 
 
Fr Window n,n,n,n 
 
Fr Window n 
 
Fr Scan All  
 
Fr Scan n 
 
Fr Scan n,n 
 
Fr Julia n,n,n 
 
Fr Mandelbrot n 
 
Open Workbench  
 
Wb To Back  
 
Wb To Front  
 
Cli Execute s$ 
 
Cli Print s$ 
 
Guru Meditation n,n 
 
n=Guru Alert(s$,s$,s$,s$,s$)
 
n=Guru Alert(s$,s$,s$,s$)
 
n=Guru Alert(s$,s$,s$)

n=Guru Alert(s$,s$)
 
n=Guru Alert(s$)
 
Multi On  
 
Multi Off  
 
Set Amos Pri n 
 
n=Amos Pri  
 
Wb Def Prefs n,n 
 
Wb Prefs n,n 
 
Set Wb Prefs n,n,n 
 
Set Wb Prefs n,n 
 
n=Sys Request(s$,s$,s$,s$,s$,s$,s$)
 
n=Sys Request(s$,s$,s$,s$,s$,s$)
 
n=Sys Request(s$,s$,s$,s$,s$)
 
n=Sys Request(s$,s$,s$,s$)

n=Sys Request(s$,s$,s$)
 
Hard Reset  
 
Warm Reset  
 
n=Hw Mouse Key  
 
n=Y Beam  
 
Beam Wait n 
 
n=Gr Ink  
 
n=Gr Back  
 
n=Gr Border  
 
Gr Centre n,s$ 
 
n=Amos Base  
 
n=Craft Version  
 
n=B.swap(n)
 
n=W.swap(n)
 
n=L.swap(n)
 
n=Cli Here  
 
n=Amos Pro  

