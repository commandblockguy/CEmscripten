const keymap = {
	ArrowDown: [7, 0],
	ArrowLeft: [7, 1],
	ArrowRight: [7, 2],
	ArrowUp: [7, 3],
	Enter: [6, 0],
	Escape: [6, 6]
}

window.addEventListener('keydown', (e) => {
	var kb_Data = ccall('get_kb_Data', 'number');

	if([32, 37, 38, 39, 40].indexOf(e.keyCode) > -1) {
        e.preventDefault();
    }

	var keynum = keymap[e.key];
	if(!keynum) {
		console.log('Unmapped:', e.key);
		return
	}
	var ptr = kb_Data + keynum[0];
	setValue(ptr, getValue(ptr, 'i8') | (1 << keynum[1]), 'i8');

	//console.log(e);
});

window.addEventListener('keyup', (e) => {
	var kb_Data = ccall('get_kb_Data', 'number');

	var keynum = keymap[e.key];
	if(!keynum) return;
	var ptr = kb_Data + keynum[0];
	setValue(ptr, getValue(ptr, 'i8') & ~(1 << keynum[1]), 'i8');

	//console.log(e);
});
