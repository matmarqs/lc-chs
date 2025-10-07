local function recurring_cycle(a, b)
	local str = ""
	local i = 1
	local dividends = {}
	while true do
		a = 10 * a
		if dividends[a] ~= nil then
			if a == 0 then
				return "0"
			else
				return string.sub(str, dividends[a], i)
			end
		end
		dividends[a] = i
		local d = math.floor(a / b)
		a = a - d * b
		str = str .. d
		i = i + 1
	end
end

local max = 0
local num = 0

for i = 1, 999 do
	local len = #recurring_cycle(1, i)
	if len > max then
		num = i
		max = len
	end
end

print(num)
