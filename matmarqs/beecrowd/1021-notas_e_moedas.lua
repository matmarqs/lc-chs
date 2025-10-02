local n = io.read("*n")

local cents = math.floor(n * 100 + 0.5)

local currency = {
	{
		title = "NOTAS",
		name = "nota",
		list = {
			10000,
			5000,
			2000,
			1000,
			500,
			200,
		},
	},
	{
		title = "MOEDAS",
		name = "moeda",
		list = {
			100,
			50,
			25,
			10,
			5,
			1,
		},
	},
}

for _, c in ipairs(currency) do
	print(c.title .. ":")
	for _, val in ipairs(c.list) do
		local x = math.floor(cents / val)
		print(string.format("%d %s(s) de R$ %.2f", x, c.name, val / 100))
		cents = cents - val * x
	end
end
