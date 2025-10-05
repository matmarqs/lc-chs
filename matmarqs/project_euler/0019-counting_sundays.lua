local function is_leap_year(y)
	if y % 400 == 0 then
		return true
	elseif y % 100 == 0 then
		return false
	elseif y % 4 == 0 then
		return true
	else
		return false
	end
end

local function get_month_days(date)
	-- april 4, june 6, september 9, november 11
	if date.m == 4 or date.m == 6 or date.m == 9 or date.m == 11 then
		return 30
	end
	if date.m == 2 then
		return is_leap_year(date.y) and 29 or 28
	end
	return 31
end

local function next_day(dt)
	local month_days = get_month_days(dt)
	if dt.m == 12 and dt.d == month_days then
		return { d = 1, m = 1, y = dt.y + 1 }
	elseif dt.d == month_days then
		return { d = 1, m = dt.m + 1, y = dt.y }
	else
		return { d = dt.d + 1, m = dt.m, y = dt.y }
	end
end

local function next_weekday(wd)
	return (wd + 1) % 7
end

local date = { d = 1, m = 1, y = 1900 }
local weekday = 0

local count = 0
while date.y <= 2000 do
	if date.y >= 1901 and weekday == 6 and date.d == 1 then
		count = count + 1
	end
	date = next_day(date)
	weekday = next_weekday(weekday)
end

print(count)
