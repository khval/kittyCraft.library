# Info

Documentation for Kitty Craft Extensions commands.

Commands listed as 
**bold**
are commands that are implemented.

Commands listed as
*italic*
are commands started on.

Command without description, are not implemented.

At bottom of the list you will find none supported commands.

# List of commands

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
 
**n=Db Free(s$)**

    returns number of blocks free on drive s$
 
**n=Db Used(s$)**

    returns number of blocks used on drive s$
 
**n=Db Size(s$)**

    returns returns the size in blocks of drive s$
 
n=Disc State(s$)

    return sate of drive
    -1 is not a DOS disk
    0 is write protected
    1 is not validated
    2 is filesystem ok, ready to use.
 
s$=Disc Type$(s$)
 
    Returns the identification code of the disk in drive

    DOS is OFS
    DOS+chr$(1) is FFS
    NDOS Not an AmigaDOS disc
    BAD Disc structure is corrupted or abnormal
    KICK a kickstart disc for Amiga 1000.

**n=File Protect(filename$)**

    Returns protection bits from filename$

**s$=File Comment$(s$)**

    Returns comment of file from filename$

**n=File Length(s$)**

    Returns length of file from filename$
 
**n=File Type(filename$)**

    Returns type of file from filename$

**Set Protect filename$,n**

    Command sets file protection bits
 
**Set Comment filename$,comment$)**

    Command sets file comment

**s$=Dr Name$(path$)**
 
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
 
**Set Red color,value**

    Set red in a color

    ECS values 0 to 15 
    AGA/VGA values 0x100 to 01FF
 
**value=Pal Red(color)**

    get value from color
    return OCS/ECS value 0 to 15
 
**Set Green color,value**

    Set green in a color

    ECS values 0 to 15 
    AGA/VGA values 0x100 to 01FF

**value=Pal Green(color)**

    get value from color
    return OCS/ECS value 0 to 15
 
**Set Blue n,n**

    Set blue in a color

    ECS values 0 to 15 
    AGA/VGA values 0x100 to 01FF
 
**value=Pal Blue(color)**

    get value from color
    return OCS/ECS value 0 to 15

**Reserve As Palette [bank number]**
 
    Reserve a bank with 1 palette.
    (Only kittyCraft, not AmosPro Craft extention) 

**Reserve As Palette [bank number],[number of palettes]**
 
    Reserve a bank with x number of palettes

    Old “AmosPro Craft extension” only reserves 32 colors in ECS format (2 bytes per color).
    “KittyCraft” reserves 256 colors in AGA/VGA format (3 bytes per color).

**n=Pal Count(n)**

    Return number of palettes reserved in bank
 
**Pal To Bank [bank number]**

    Copy current screen colors to [bank number]

**Pal To Bank [bank number],[palette number]**

    Copy current screen colors to [bank number] with [palette number]

Pal To Bank [bank number],[palette number],[mask]
 
 --- don't know how mask works... (so not working yet.)
 
**Pal From Bank [bank number]**

    Copy colors from bank to screen

**Pal From Bank [bank number],[palette number]**

    Copy colors from [bank number] with [palette number] to screen

Pal From Bank [bank number],[palette number],[mask]

--- don't know how mask works... (so not working yet.)

**Pal Spread [color index 1] To [color index 2]**

    Mix colors between color index 1 to color index 2

**Pal Copy [color1] To [color2]**

    Copy RGB value from color1 to color2

**Pal Swap [color1],[color2]**

    Swap two colors

**Pal Swap Bank [bank]**

    Swaps the current palette with the bank 
 
**Pal Swap Bank [bank],[color]**

    Swaps the current palette with the bank, starting with [color].

Pal Swap Bank [bank],[color],[mask]

    Swaps the current palette with the bank, starting with [color].
    mask limits the colors transfared to the bank.

**Set Bank Colour [bank number],[palette],[color number],[value]**

    Changes the [color number] in [palette] in the [bank number] with [value]

    There are two options for values.

    [value] is in the range $000 to $FFF for OCS/ECS
    [value] is in the range $FF000000 to $FFFFFFFF for 24bit RGB (VGA/AGA)
 
**n=Bank Colour([bank number],[palette],[color index])**

    Returns the color in [color index] of [palette] stored in [bank number].
 
**Del Bank Colour [bank number],[palette],[color index]**

    Deletes color from bank.
    After deleting color, it will be ignoring when using “Pal from bank” command.

    (Using Bank Colour on a deleted color will return $FFF.)
 
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
 
**Open Workbench**

    Amos Kittens will never close Workbench to save memory, 
    so this command should not do anything.

**Wb To Back**

    This command does not do anything.

**Wb To Front**

    This command does not do anything.
 
**Cli Execute [script$]**
 
    Pipe script and execute the commands from pipe.

**Cli Print s$**

    Print text to shell / cli
 
Guru Meditation n,n 

**n=Guru Alert(s1$)**

**n=Guru Alert(s1$,s2$)**

**n=Guru Alert(s1$,s2$,s3$)**

**n=Guru Alert(s1$,s2$,s3$,s4$)**

**n=Guru Alert(s1$,s2$,s3$,s4$,s5$)**

    Show an old-style Guru Alert message, 
    (don’t worry totally safe as it’s a fake Guru.)
    Command takes 1 to 5 text string, etch text represents a line.

    Command returns mouse button pressed.
 
**Multi On**

    Enable multitasking, calls function exec.library/permit()
 
**Multi Off**

    Disable multitasking, executes function exec.library/forbid()

    Do not abuse this command, on AmigaOS4.1 the mouse, keyboard, audio needs multitasking, disabling multitasking for a long time course bad sound, keyboard / mouse locking up, and other issues, 

    If you need safe atomic protection, look at the OS4.1 SDK in the folder. 
    “SDK:Documentation/Autodocs/exec.h”, See functions MutexObtain() and MutexRelease().

    Only when it written you most disable multitasking, should you disable multitasking,
    and when you keep the multitasking disabled as short as possible.

**Set Amos Pri n**

    This command sets task pri of Amos Kittens.
 
**n=Amos Pri**

    This command should returns Amos Kittens Pri.

    (this command is broken in AmosPro Craft extension.)
 
**n=Sys Request(s1$,Ok$,Cancel$)**

**n=Sys Request(s1$,s2$,Ok$,Cancel$)**

**n=Sys Request(s1$,s2$,s3$,Ok$,Cancel$)**

**n=Sys Request(s1$,s2$,s3$,s4$,Ok$,Cancel$)**

**n=Sys Request(s1$,s2$,s3$,s4$,s5$,Ok$,Cancel$)**

    Display system requestor 

    S1$ to S5$ is text lines in the requestor.
    Ok$ is OK bottom, returns true.
    Cancel$ is Cancel button, returns false.
    (Your are allowed on Amos kittens to hack the buttons using “|” symbol, 
        this will insert more buttons.)

n=Hw Mouse Key  
 
**n=Gr Ink**

    Returns ink1
 
**n=Gr Back**
 
    Returns ink2

**n=Gr Border**
 
    Returns ink3

Gr Centre n,s$ 
  
**n=Craft Version**

    Returns verson of the kittycraft extention / library version.
 
**n=B.swap(n)**

    Swaps high and low nibble in a byte, 
    if number is larger then a byte then upper bits are masked out.

    $FFFFFF21 becomes $12

**n=W.swap(n)**

    Swaps high and low byte in a word / (int16), 
    if number is larger then a word then upper bits are masked out.

    $FFFF0201 becomes $0102
 
**n=L.swap(n)**

    Swaps high and low word in a long / (int32), 

    $04030201 becomes $02010403

**n=Cli Here**

    Returns always TRUE.

**n=Amos Pro**

    Returns always TRUE.

# The following commands are not supported.

Wb Def Prefs [address],[length] 

    Does the same as bload more or less, but copies the prefs file to bank

    Command will return error if executed.

Wb Prefs [address],[length]  
 
    Does the same as bload more or less, but copies the prefs file to bank

    Command will return error if executed.

Set Wb Prefs n,n,n 
 
    Prefs files are not backwards compatible, not vice to peek and poke into systems files.
    Until AmigaOS adapts JSON or XML prefs or provide a standard software API, we should not do this.

    Command will return error if executed.

Set Wb Prefs n,n 

    Prefs files are not backwards compatible, not vice to peek and poke into systems files.
    Until AmigaOS adapts JSON or XML prefs or provide a standard software API, we should not do this.

    Command will return error if executed.

n=Amos Base  

    Its not legal to poke into Amos Kitty Base, 
    as its not the same as Amos Base.

    Command will return error if executed.

Hard Reset  
 
    Technically possible, but do we really want to allow this?

    Command will return error if executed.

Warm Reset  

    Technically possible, but do we really want to allow this?

    Command will return error if executed.

n=Y Beam  

    Rendering engine is technically not in Amos Kittens, its in retroMode,
    rendering position is not exposed.

    Command will return error if executed.

Beam Wait n

    Rendering engine is technically not in Amos Kittens, its in retroMode,
    rendering position is not exposed.

    Command will return error if executed.