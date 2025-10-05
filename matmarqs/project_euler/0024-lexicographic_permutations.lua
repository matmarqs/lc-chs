-- this solution is actually very bad
-- $ time luajit 0024-lexicographic_permutations.lua
-- real    0m8.751s
-- user    0m8.083s
-- sys     0m0.627s

--local dump_table = require("utils").dump_table
local digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }

local function copy_table(t)
	local copy = {}
	for k, v in pairs(t) do
		copy[k] = v
	end
	return copy
end

local function concat(element, t)
	table.insert(t, 1, element)
	return t
end

local function permutations(t)
	if #t == 1 then
		return { t }
	end

	local new_perms = {}
	for index, element in ipairs(t) do
		local tcopy = copy_table(t)
		table.remove(tcopy, index)
		local perms = permutations(tcopy)
		for _, perm in ipairs(perms) do
			new_perms[#new_perms + 1] = concat(element, perm)
		end
	end
	return new_perms
end

local perms = permutations(digits)
print(table.concat(perms[1000000], ""))
