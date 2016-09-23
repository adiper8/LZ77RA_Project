#include "LZ77Main.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <cstdlib>
#include <bitset>

#include <msclr\marshal_cppstd.h>


	//! Number of code words
	unsigned int numberOfCodeWords = 0;
	//! indicate if a match starts
	bool isStartMatch = true;
	//! secondary index
	unsigned int secondIndex = 0;
	//! offset to the longest match that starts in the dictionary
	unsigned int offset = 0;
	//! the actual index the longest match that starts
	unsigned int position = 0;
	//! temporary variable
	std::string tmpString;
	//! string should write to the file.
	std::string stringToOutput;
	//! the longest match string
	std::string longestMatch;
	//! The next character after the longest match in the buffer
	std::string nextChar;
	//! Buffer
	std::string buffer;
	//! output file
	std::ofstream outputFile;

	//! output file 2
	std::ofstream outputFile2;

	//! Compressed string
	std::string compressedString;

	static int debugCounter = 0;

	/*###############################*/
	//Number of enable mistakes
	int k = 3;
	/*###############################*/

	unsigned long long int decimal_binary(int n)  /* Function to convert decimal to binary.*/
	{
		unsigned long long int rem, i = 1, binary = 0;

		while (n != 0)
		{
			rem = n % 2;
			n /= 2;
			binary += rem*i;
			i *= 10;
		}
		return binary;
	}

	//This function find in each lower index the lonegst match string
	void findLonestMatch(std::string buffer, unsigned int index, unsigned int lengthOfString)
	{
		//! go over for each character that smaller than cursor.
		for (secondIndex = 0; secondIndex < index; secondIndex++)
		{
			unsigned int tmpIndex = index;
			unsigned int tmpSecondIndex = secondIndex;
			//! find the longest match.
			while (tmpIndex < lengthOfString && buffer[tmpSecondIndex] == buffer[tmpIndex])
			{
				if (isStartMatch)
				{
					position = tmpSecondIndex;
					isStartMatch = false;
				}
				tmpString.push_back(buffer[tmpSecondIndex]);
				tmpSecondIndex++;
				tmpIndex++;
			}
			isStartMatch = true;

			//checks whether the current match is the longest match so far.
			if (longestMatch.length() < tmpString.length())
			{
				longestMatch = tmpString;
				offset = index - position;
			}
			tmpString.clear();
		}
	}

	//This function mark specified index as mistake
	void markAsMistake(std::string& buffer, unsigned int index)
	{
		if (buffer[index] == '0')
		{
			buffer[index] = '1';
		}
		else
		{
			buffer[index] = '0';
		}
	}

	//Find the max ratio, take the higher index.
	unsigned int findMax(double arr[], int length)
	{
		unsigned int indexToReturn = length;

		for (int i = length; i > 0; i--)
		{
			if (arr[indexToReturn] < arr[i])
			{
				indexToReturn = i;
			}
		}

		if (arr[0] >= arr[indexToReturn])
			indexToReturn = 0;

		return indexToReturn;
	}

	//This function should return the number of times the word appears in the buffer
	int foreCast(const int startIndex, const std::string& buffer, const std::string& word)
	{
		int count = 0;

		//Checks if the word greater than the buffer
		if (word.length() > buffer.length())
		{
			return 0;
		}

		int j = 0;
		int i = startIndex;
		while (i < buffer.length())
		{
			//tmp index
			int k = i;

			//Checks matches
			while (buffer[i] == word[j] && i < buffer.length())
			{
				i++;
				j++;
			}

			//The word has been matched
			if (j == word.length())
			{
				count++;
			}

			i = ++k;
			j = 0;
		}

		return count;
	}

	//This function preapre the correct string with the properly numebr of mistakes
	std::string wrapper(std::string src_buffer, int k, unsigned int index, unsigned int lengthOfString,
		double ratioMistake[], int indexesMistake[])
	{
		std::string srcBufferToReturn = src_buffer;

		for (int i = 0; i <= k; i++)
		{
			findLonestMatch(src_buffer, index, lengthOfString);

			int countInFurther = foreCast((index + longestMatch.length()), src_buffer, longestMatch);
			//(i+1) number of mistakes

			if (i == 0)
				ratioMistake[i] = static_cast<double>(longestMatch.length()) + countInFurther;
			else
				ratioMistake[i] = (static_cast<double>(longestMatch.length()) / (i)) + countInFurther;

			//Mark the charcter that does'nt seem so far as mistake
			if (index + longestMatch.length() < src_buffer.length())
			{
				markAsMistake(src_buffer, index + longestMatch.length());
				indexesMistake[i] = index + longestMatch.length();
			}

			//Initialize
			longestMatch.clear();
			offset = 0;
		}

		int numberOfMistakes = findMax(ratioMistake, k);

		for (int i = 0; i < numberOfMistakes; i++)
		{
			markAsMistake(srcBufferToReturn, indexesMistake[i]);
		}


		return srcBufferToReturn;
	}

	void
		LZ771::LZ77Main::doCompression()
	{
		outputFile2.open("LZ77_Compressed.txt", std::ofstream::out | std::ofstream::trunc);
		outputFile2.close();
		outputFile2.open("LZ77_Compressed.txt", std::ofstream::out | std::ofstream::trunc);

		outputFile.open("LZ77_Result.txt", std::ofstream::out | std::ofstream::trunc);
		outputFile.close();
		outputFile.open("LZ77_Result.txt", std::ofstream::out | std::ofstream::trunc);

		msclr::interop::marshal_context context;
		System::String^ managedString = this->pathFile->Text;
		System::String^ inputNumOfMistakes = this->numOfMistakesText->Text;
		std::string standardString = context.marshal_as<std::string>(managedString);
		std::string StringinputNumOfMistakes = context.marshal_as<std::string>(inputNumOfMistakes);

		if (StringinputNumOfMistakes != "")
			k = std::stoi(StringinputNumOfMistakes);

		//! input file
		std::ifstream SourceFile(standardString);

		//! main index
		unsigned int index = 0;
		//! The number of characters in original string
		unsigned int lengthOfString = 0;

		//Checks validation of the file
		if (SourceFile.is_open())
		{
			//Save the String on the buffer
			getline(SourceFile, buffer);

			SourceFile.close();
		}
		lengthOfString = buffer.length();

		//log 2 of the source string size
		double log2Size = ceil(log2(lengthOfString));

		std::cout << "Read from: " << standardString << " , The string size is: " << lengthOfString << std::endl;
		outputFile << "Read from: " << standardString << " , The string size is: " << lengthOfString << std::endl;

		std::cout << "Template: <offset, longestMatch.length(), next char>" << std::endl;
		outputFile << "Template: <offset, longestMatch.length(), next char>" << std::endl;

		bool debug1 = outputFile.is_open();
		bool debug2 = outputFile2.is_open();

		if (outputFile.is_open() && outputFile2.is_open())
		{
			double* ratioMistake = new double[k + 1];
			int* indexesMistake = new int[k + 1];

			//! go over for each character in source string.
			while (index < lengthOfString)
			{
				//Checks if the running is LZ with mistakes
				if (this->isLZWithMistakes->Checked)
				{
					//Mark as comment the wrapper calling to use LZ77 only
					if (index != 0)
						buffer = wrapper(buffer, k, index, lengthOfString, ratioMistake, indexesMistake);
				}

				findLonestMatch(buffer, index, lengthOfString);

				//! determine the next char after the longest match.
				stringToOutput = longestMatch;
				compressedString += stringToOutput;
				if (index + longestMatch.length() < lengthOfString)
				{
					stringToOutput.push_back(buffer[index + longestMatch.length()]);
					nextChar = buffer[index + longestMatch.length()];
				}
				else
				{
					nextChar = "$";
				}

				compressedString += nextChar;

				index += longestMatch.length() + 1;

				debugCounter++;
				unsigned long long int binOffset = decimal_binary(offset);
				std::string stringOffset = std::to_string(binOffset);

				unsigned long long int binLength = decimal_binary(longestMatch.length());
				std::string stringLength = std::to_string(binLength);

				int numberZeros = log2Size - stringOffset.size();
				std::string rest_zeroOffset(numberZeros, '0');

				numberZeros = log2Size - stringLength.size();
				std::string rest_zeroLength(numberZeros, '0');

				//! print the longest match and the next character
				if (stringToOutput.length() > 0)
				{
					std::string outputString = rest_zeroOffset + stringOffset + rest_zeroLength + stringLength + nextChar;
					int debug = outputString.size();

					std::cout << stringToOutput << "  <" << offset << ", " << longestMatch.length() << ", " << nextChar << ">" << std::endl;
					outputFile << stringToOutput << "  <" << offset << ", " << longestMatch.length() << ", " << nextChar << ">" << std::endl;
					outputFile2 << outputString;
				}

				//initialize variables
				longestMatch.clear();
				stringToOutput.clear();
				nextChar.clear();
				offset = 0;
				numberOfCodeWords++;
			} //end main loop

			  //Calculate the new size of compressed string
			unsigned int comprassedSize = numberOfCodeWords * ((2 * (static_cast<int>(log2Size))) + 1);

			double ratio = static_cast<double>(comprassedSize) / static_cast<double>(lengthOfString);

			//reset the number of words for next execution
			numberOfCodeWords = 0;

			std::cout << "The compressed string size is: " << comprassedSize << std::endl;
			outputFile << "The compressed string size is: " << comprassedSize << std::endl;
			std::cout << "The ratio compression is: " << ratio << std::endl;
			outputFile << "The ratio compression is: " << ratio << std::endl;

			delete ratioMistake;
			delete indexesMistake;

			outputFile.close();
			outputFile2.close();
		}
	}

	using namespace System;
	using namespace System::Windows::Forms;
	[STAThread]
	void main()
	{
		Application::EnableVisualStyles();
		Application::SetCompatibleTextRenderingDefault(false);

		LZ771::LZ77Main form;

		Application::Run(%form);
	}
