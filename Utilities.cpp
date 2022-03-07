

#include "Utilities.h"

void Utilities::setFieldWidth(unsigned int w) {
    m_widthField = w;
}

unsigned int Utilities::getFieldWidth() const {
    return m_widthField;
}

string Utilities::extractToken(const string& str, size_t& next_pos, bool& more) {

		size_t pos = str.find(m_delimiter, next_pos);

		if (pos == next_pos) {
			more = false;
			throw "there are two delimiters with no token";
		}

		else {
			more = (pos != string::npos) ? true : false;
			string tokenExtracted = str.substr(next_pos, pos - next_pos);
			next_pos = pos + 1;
			if (tokenExtracted.size() > m_widthField)
				m_widthField = tokenExtracted.length();

			return tokenExtracted;
		}
	}
void Utilities::setDelimiter(char c) {
    m_delimiter = c;
}

char Utilities::getDelimiter() {
    return m_delimiter;
}
