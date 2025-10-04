local rawdata = {
	{ 3 },
	{ 7, 4 },
	{ 2, 4, 6 },
	{ 8, 5, 9, 3 },
}

--local rawdata = {
--	{ 75 },
--	{ 95, 64 },
--	{ 17, 47, 82 },
--	{ 18, 35, 87, 10 },
--	{ 20, 04, 82, 47, 65 },
--	{ 19, 01, 23, 75, 03, 34 },
--	{ 88, 02, 77, 73, 07, 63, 67 },
--	{ 99, 65, 04, 28, 06, 16, 70, 92 },
--	{ 41, 41, 26, 56, 83, 40, 80, 70, 33 },
--	{ 41, 48, 72, 33, 47, 32, 37, 16, 94, 29 },
--	{ 53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14 },
--	{ 70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57 },
--	{ 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48 },
--	{ 63, 66, 04, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31 },
--	{ 04, 62, 98, 27, 23, 09, 70, 98, 73, 93, 38, 53, 60, 04, 23 },
--}

local tree = {}

for i, line in ipairs(rawdata) do
	for _, val in ipairs(line) do
		table.insert(tree, { val, i })
	end
end

local function level(i)
	return tree[i][2]
end

local function left_child(i)
	return i + level(i)
end

local function right_child(i)
	return left_child(i) + 1
end

local max_path_sum_table = {}

local function max_path_sum(i)
	if tree[i] == nil then
		return 0
	end
	local left = (max_path_sum_table[left_child(i)] ~= nil) and max_path_sum_table[left_child(i)]
		or max_path_sum(left_child(i))
	local right = (max_path_sum_table[right_child(i)] ~= nil) and max_path_sum_table[right_child(i)]
		or max_path_sum(right_child(i))
	max_path_sum_table[i] = tree[i][1] + math.max(left, right)
	return max_path_sum_table[i]
end

print(max_path_sum(1))
