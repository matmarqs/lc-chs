local size = 1001

local n = 1
local m = 1
local sum = 1

while m < size do
	for _ = 1, 4 do
		n = n + (m + 1)
		sum = sum + n
	end
	m = m + 2
end

print(sum)
