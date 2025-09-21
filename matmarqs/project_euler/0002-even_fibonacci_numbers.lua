-- find the sum of all even F_n <= 4.000.000

local f0 = 0
local f1 = 1
local f2 = 1

local sum = 0

while f2 <= 4000000 do
	f2 = f1 + f0
	if f2 % 2 == 0 then
		sum = sum + f2
	end
	f0 = f1
	f1 = f2
end

print(sum)
