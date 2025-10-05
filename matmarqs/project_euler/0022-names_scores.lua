local utils = require("utils")

local content = utils.read_file("0022_names.txt")

local names = {}
for str in string.gmatch(content, '"(%w+)"') do
	names[#names + 1] = str
end
table.sort(names)

local function alphabetical_value(name)
	local sum = 0
	for i = 1, #name do
		sum = sum + string.byte(name, i) - 64 -- 64 = decimal ASCII code of '@', 65 = 'A'
	end
	return sum
end

local sum = 0
for i, name in ipairs(names) do
	sum = sum + alphabetical_value(name) * i
end
print(sum)

--utils.dump_table(names)
