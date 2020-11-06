const key_bits = {
	"Graph":     [1, 0],
	"Trace":     [1, 1],
	"Zoom":      [1, 2],
	"Window":    [1, 3],
	"Yequ":      [1, 4],
	"2nd":       [1, 5],
	"Mode":      [1, 6],
	"Del":       [1, 7],

	"Store":     [2, 1],
	"Ln":        [2, 2],
	"Log":       [2, 3],
	"Square":    [2, 4],
	"Recip":     [2, 5],
	"Math":      [2, 6],
	"Alpha":     [2, 7],

	"0":         [3, 0],
	"1":         [3, 1],
	"4":         [3, 2],
	"7":         [3, 3],
	"Comma":     [3, 4],
	"Sin":       [3, 5],
	"Apps":      [3, 6],
	"GraphVar":  [3, 7],

	"DecPnt":    [4, 0],
	"2":         [4, 1],
	"5":         [4, 2],
	"8":         [4, 3],
	"LParen":    [4, 4],
	"Cos":       [4, 5],
	"Prgm":      [4, 6],
	"Stat":      [4, 7],

	"Chs":       [5, 0],
	"3":         [5, 1],
	"6":         [5, 2],
	"9":         [5, 3],
	"RParen":    [5, 4],
	"Tan":       [5, 5],
	"Vars":      [5, 6],

	"Enter":     [6, 0],
	"Add":       [6, 1],
	"Sub":       [6, 2],
	"Mul":       [6, 3],
	"Div":       [6, 4],
	"Power":     [6, 5],
	"Clear":     [6, 6],

	"Down":      [7, 0],
	"Left":      [7, 1],
	"Right":     [7, 2],
	"Up":        [7, 3],
}

const default_keymap = {
	"Unidentified":	null,
	"Alt":			null,
	"AltGraph":		null,
	"CapsLock":		null,
	"Control":		null,
	"Fn":			null,
	"FnLock":		null,
	"Hyper":		null,
	"Meta":			null,
	"NumLock":		null,
	"ScrollLock":	null,
	"Shift":		null,
	"Super":		null,
	"Symbol":		null,
	"SymbolLock":	null,
	"Enter":		"Enter",
	"Tab":			"2nd",
	" ":			"0",
	"ArrowDown":	"Down",
	"ArrowLeft":	"Left",
	"ArrowRight":	"Right",
	"ArrowUp":		"Up",
	"End":			"Stat",
	"Home":			"Mode",
	"PageDown":		"Prgm",
	"PageUp":		"Apps",
	"Backspace":	"Mode",
	"Clear":		"Clear",
	"Delete":		"Del",
	"Insert":		"Del",
	"Escape":		"Clear",
	"F1":			"Yequ",
	"F2":			"Window",
	"F3":			"Zoom",
	"F4":			"Trace",
	"F5":			"Graph",
	"`":			"Ln",
	"1":			"1",
	"2":			"2",
	"3":			"3",
	"4":			"4",
	"5":			"5",
	"6":			"6",
	"7":			"7",
	"8":			"8",
	"9":			"9",
	"0":			"0",
	"-":			"Sub",
	"=":			"Math",
	"a":			"Math",
	"b":			"Apps",
	"c":			"Prgm",
	"d":			"Recip",
	"e":			"Sin",
	"f":			"Cos",
	"g":			"Tan",
	"h":			"Power",
	"i":			"Square",
	"j":			"Comma",
	"k":			"LParen",
	"l":			"RParen",
	"m":			"Div",
	"n":			"Log",
	"o":			"7",
	"p":			"8",
	"q":			"9",
	"r":			"Mul",
	"s":			"Ln",
	"t":			"4",
	"u":			"5",
	"v":			"6",
	"w":			"Sub",
	"x":			"Store",
	"y":			"1",
	"z":			"2",
	"A":			"Math",
	"B":			"Apps",
	"C":			"Prgm",
	"D":			"Recip",
	"E":			"Sin",
	"F":			"Cos",
	"G":			"Tan",
	"H":			"Power",
	"I":			"Square",
	"J":			"Comma",
	"K":			"LParen",
	"L":			"RParen",
	"M":			"Div",
	"N":			"Log",
	"O":			"7",
	"P":			"8",
	"Q":			"9",
	"R":			"Mul",
	"S":			"Ln",
	"T":			"4",
	"U":			"5",
	"V":			"6",
	"W":			"Sub",
	"X":			"Store",
	"Y":			"1",
	"Z":			"2",
	"[":			"Mul",
	"]":			"Sub",
	"\\":			"Recip",
	";":			"2nd",
	"'":			"Alpha",
	",":			"Comma",
	".":			"DecPnt",
	"/":			"Div",
	"~":			"Chs",
	"!":			"Log",
	"@":			"Square",
	"#":			"3",
	"$":			"Sin",
	"%":			"Cos",
	"^":			"Power",
	"&":			"Tan",
	"*":			"Mul",
	"(":			"LParen",
	")":			"RParen",
	"_":			"GraphVar",
	"+":			"Add",
	"{":			"LParen",
	"}":			"RParen",
	"|":			"Vars",
	":":			"DecPnt",
	"\"":			"Add",
	"<":			"Vars",
	">":			"Store",
	"?":			"Chs",
}

Module.kb_Data = null;

window.addEventListener('keydown', async (e) => {
	if(!Module.kb_Data) Module.kb_Data = await ccall('get_kb_Data', 'number');

	e.preventDefault();

    var key_name = default_keymap[e.key];
    if(!key_name) {
    	if(key_name !== null) {
			console.log('Unmapped:', e.key);
		}
		return;
	}
	var keynum = key_bits[key_name];
	if(!keynum) {
		console.log('No keypad key:', key_name);
		return;
	}
	var ptr = Module.kb_Data + keynum[0];
	setValue(ptr, getValue(ptr, 'i8') | (1 << keynum[1]), 'i8');
});

window.addEventListener('keyup', (e) => {
	if(!Module.kb_Data) Module.kb_Data = ccall('get_kb_Data', 'number');

	var key_name = default_keymap[e.key];
	if(!key_name) return;
	var keynum = key_bits[key_name];
	if(!keynum) {
		console.log('No keypad key:', key_name);
		return;
	}
	var ptr = Module.kb_Data + keynum[0];
	setValue(ptr, getValue(ptr, 'i8') & ~(1 << keynum[1]), 'i8');
});
