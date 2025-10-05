local nt = require("nt")

local tests = {
	gcd = function()
		local header = "gcd failed: "
		local function test(a, b, expected)
			local actual = nt.gcd(a, b)
			assert(
				actual == expected,
				header .. ("expected gcd(%s, %s) = %d but got %s"):format(a, b, expected, actual)
			)
		end
		test(18, 90, 18)
	end,

	lcm = function()
		local header = "lcm failed: "
		local function test(a, b, expected)
			local actual = nt.lcm(a, b)
			assert(
				actual == expected,
				header .. ("expected lcm(%s, %s) = %s but got %s"):format(a, b, expected, actual)
			)
		end
		test(92, 12, 276)
	end,

	prime_decomposition = function()
		local header = "get_prime_decomposition failed: "
		local function test(n, expected)
			local actual = nt.get_prime_decomposition(n)
			for p, c in pairs(expected) do
				assert(actual[p] == c, header .. ("expected %s^%s but got %s"):format(p, c, actual[p]))
			end
			for p, c in pairs(actual) do
				assert(expected[p] == c, header .. ("unexpected factor %s^%s"):format(p, c))
			end
		end
		test(70, { [2] = 1, [5] = 1, [7] = 1 })
	end,

	is_prime = function()
		local header = "is_prime failed: "
		local function test(n, expected)
			local actual = nt.is_prime(n)
			assert(actual == expected, header .. ("expected is_prime(%s) = %s but got %s"):format(n, expected, actual))
		end
		test(31, true)
	end,

	nth_prime = function()
		local header = "nth_prime failed: "
		local function test(n, expected)
			local actual = nt.nth_prime(n)
			assert(actual == expected, header .. ("expected nth_prime(%s) = %s but got %s"):format(n, expected, actual))
		end
		test(8, 19)
	end,

	sum_of_proper_divisors = function()
		local header = "sum_of_proper_divisors failed: "
		local function test(n, expected)
			local actual = nt.sum_of_proper_divisors(n)
			assert(
				actual == expected,
				header .. ("expected sum_of_proper_divisors(%s) = %s but got %s"):format(n, expected, actual)
			)
		end
		test(28, 28)
		test(220, 284)
		test(284, 220)
		test(10, 8)
	end,
}

for _, test in pairs(tests) do
	test()
end

print("ALL TESTS PASSED!")
