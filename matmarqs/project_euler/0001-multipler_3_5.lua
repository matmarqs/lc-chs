-- find the sum of all the multiple of 3 or 5 below 1000

local sum = 0

for n = 1, 999 do
	if n % 3 == 0 or n % 5 == 0 then
		sum = sum + n
	end
end

print(sum)
