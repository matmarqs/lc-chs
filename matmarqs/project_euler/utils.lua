local M = {}

local function print_table(t, depth)
	print(string.rep("  ", depth) .. "{")
	for key, val in pairs(t) do
		if type(val) == "table" then
			print_table(val, depth + 1)
		else
			print(string.rep("  ", depth + 1) .. string.format("%s: %s", key, val))
		end
	end
	print(string.rep("  ", depth) .. "}")
end

function M.display_table(t)
	print_table(t, 0)
end

return M
