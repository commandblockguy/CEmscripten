mergeInto(LibraryManager.library, {
	rtc_Time: function() {
		var date = new Date;
		var seconds = date.getSeconds();
		var minutes = date.getMinutes() << 6;
		var hours = date.getHours() << 12;
		var days = ((Math.floor(date - new Date("Jan 1 1970")) / 86400000) & 0x7fff) << 17;
		return seconds | minutes | hours | days;
	},
	set_timer_Control__deps: ['update_timer_Counter'],
	set_timer_Control: function(x) {
		for(let i = 1; i <= 3; i++) {
			_update_timer_Counter(i);
			let timer = Module.timers[i - 1];
			timer.active = (x & (1 << 3*(i - 1))) > 0;
			if(x & (1 << (3*(i - 1) + 1))) timer.frequency = 32678;
			else timer.frequency = 48000000;
			timer.int = (x & (1 << (3*(i - 1) + 2))) > 0;
			timer.count_up = (x & (1 << (8 + i))) > 0;
		}
	},
	update_timer_Counter: function(x) {
		let timer = Module.timers[x - 1];
		let new_epoch = new Date;
		let diff_ms = new_epoch - timer.epoch;
		timer.epoch = new_epoch;
		if(!timer.active) return;
		let diff = timer.frequency * diff_ms / 1000;
		// todo: counting down
		timer.offset += diff;
	},
	get_timer_Counter__deps: ['update_timer_Counter'],
	get_timer_Counter: function(x) {
		_update_timer_Counter(x);
		let timer = Module.timers[x - 1];
		return timer.offset;
	},
	set_timer_Counter: function(x, n) {
		let timer = Module.timers[x - 1];
		timer.offset = n;
		timer.epoch = new Date;
	}
});
