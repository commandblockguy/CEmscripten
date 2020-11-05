mergeInto(LibraryManager.library, {
	rtc_Time: function() {
		var date = new Date;
		var seconds = date.getSeconds();
		var minutes = date.getMinutes() << 6;
		var hours = date.getHours() << 12;
		var days = ((Math.floor(date - new Date("Jan 1 1970")) / 86400000) & 0x7fff) << 17;
		return seconds | minutes | hours | days;
	}
});