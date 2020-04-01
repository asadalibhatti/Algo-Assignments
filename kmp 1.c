
#include <cstddef>
#include <cstring>
#include <vector>

const char *kmpSearch(const char *pattern, const char *text) {
	if (pattern[0] == '\0')
		return text;  // Immediate match
	
	// Compute longest suffix-prefix table
	std::vector<std::size_t> lsp;
	lsp.reserve(std::strlen(pattern));
	lsp.push_back(0);
	for (const char *pat = &pattern[1]; *pat != '\0'; pat++) {
		std::size_t j = lsp.back();  // Start by assuming we're extending the previous LSP
		while (j > 0 && *pat != pattern[j])
			j = lsp.at(j - 1);
		if (*pat == pattern[j])
			j++;
		lsp.push_back(j);
	}
	
	// Walk through text string
	for (std::size_t j = 0; *text != '\0'; text++) {  // j is the number of chars matched in pattern
		while (j > 0 && *text != pattern[j])
			j = lsp.at(j - 1);  // Fall back in the pattern
		if (*text == pattern[j]) {
			j++;  // Next char matched, increment position
			if (j == lsp.size())
				return text - (j - 1);
		}
	}
	return nullptr;  // Not found
}