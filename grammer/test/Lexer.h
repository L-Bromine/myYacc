#pragma once
#include <map>
#include <vector>
#include <string>
struct Token
{
	int type = -1;
	std::string value;
	Token() = default;
	Token(int,const std::vector<char>&);
	Token(int);
};
class LEXER
{
private:
	int nowState = 0;
	std::map<char, int> chars = {
{ '9', 0 },
{ 'R', 1 },
{ '"', 2 },
{ 'd', 3 },
{ 'g', 4 },
{ 'o', 5 },
{ 'Q', 6 },
{ '\n', 7 },
{ 'c', 8 },
{ '<', 9 },
{ 'P', 10 },
{ 'N', 11 },
{ '8', 12 },
{ 'y', 13 },
{ 'w', 14 },
{ '[', 15 },
{ '+', 16 },
{ 'e', 17 },
{ 'U', 18 },
{ 'q', 19 },
{ 'E', 20 },
{ 'n', 21 },
{ '-', 22 },
{ '4', 23 },
{ '!', 24 },
{ 'Z', 25 },
{ 'l', 26 },
{ '_', 27 },
{ 's', 28 },
{ 'z', 29 },
{ '\\', 30 },
{ 'a', 31 },
{ 'f', 32 },
{ '^', 33 },
{ 'F', 34 },
{ 'K', 35 },
{ 'D', 36 },
{ '/', 37 },
{ 'X', 38 },
{ '.', 39 },
{ 'p', 40 },
{ '>', 41 },
{ 'H', 42 },
{ '$', 43 },
{ '5', 44 },
{ 'T', 45 },
{ ')', 46 },
{ '0', 47 },
{ ':', 48 },
{ 'j', 49 },
{ 'M', 50 },
{ 'h', 51 },
{ ' ', 52 },
{ '#', 53 },
{ 'I', 54 },
{ '%', 55 },
{ '&', 56 },
{ 'Y', 57 },
{ 'x', 58 },
{ '{', 59 },
{ 'u', 60 },
{ '7', 61 },
{ ',', 62 },
{ 'k', 63 },
{ 'O', 64 },
{ 'L', 65 },
{ 'i', 66 },
{ ']', 67 },
{ '3', 68 },
{ 'A', 69 },
{ 't', 70 },
{ ';', 71 },
{ '}', 72 },
{ 'v', 73 },
{ 'V', 74 },
{ '6', 75 },
{ 'm', 76 },
{ '1', 77 },
{ 'G', 78 },
{ '=', 79 },
{ 'B', 80 },
{ 'J', 81 },
{ 'S', 82 },
{ '2', 83 },
{ 'r', 84 },
{ '(', 85 },
{ 'b', 86 },
{ '|', 87 },
{ 'C', 88 },
{ '*', 89 },
{ 'W', 90 },
	};
	int states[90][93] = {
{1, 3, 2, 3, 4, 3, 3, -1, 5, 6, 3, 3, 1, 3, 7, 8, 9, 10, 3, 3, 3, 3, 11, 1, 12, 3, 3, 3, 3, 3, -1, 3, 3, -1, 3, 3, 3, 13, 3, -1, 14, 15, 3, -1, 1, 3, 16, 1, -1, 3, 3, 3, -1, -1, 3, 17, 18, 3, 3, 19, 3, 1, 20, 3, 3, 3, 21, 22, 1, 3, 3, 23, 24, 25, 3, 1, 26, 1, 3, 27, 3, 3, 3, 1, 28, 29, 30, 31, 3, 32, 3, -1, },
{1, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, 1, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, 1, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, 1, -37, -37, 1, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, -37, 1, -37, -37, -37, -37, -37, -37, 1, -37, -37, -37, -37, -37, -37, 1, -37, 1, -37, -37, -37, -37, -37, 1, -37, -37, -37, -37, -37, -37, -37, -37, },
{2, 2, 88, 2, 2, 2, 2, -1, 2, -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, -1, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 83, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 74, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{-22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, 73, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, -22, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 69, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{-33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, -33, },
{-16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, -16, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 66, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{-17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, -17, },
{-9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, 65, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, -9, },
{-20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, 60, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, -20, 61, -20, -20, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 55, -38, 3, -38, 3, -38, 3, -38, },
{-24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, 54, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, -24, },
{-32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, -32, },
{-21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, -21, },
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 53, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, },
{-35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, -35, },
{-30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, -30, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 50, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 51, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{-34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, -34, },
{-29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, -29, },
{-36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, -36, },
{3, 3, -38, 3, 3, 47, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 44, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{-28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, 43, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, -28, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{-31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, -31, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 34, -38, 3, -38, 3, -38, 3, -38, },
{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 33, -1, -1, -1, -1, },
{-19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, -19, },
{-11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, -11, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 35, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 36, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 37, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -5, 3, 3, 3, 3, -5, 3, -5, 3, 3, 3, 3, 3, -5, -5, 3, 3, 3, 3, 3, -5, 3, -5, 3, 3, 3, 3, 3, -5, 3, 3, -5, 3, 3, 3, -5, 3, -5, 3, -5, 3, -5, 3, 3, -5, 3, -5, 3, 3, 3, -5, -5, 3, -5, -5, 3, 3, -5, 3, 3, -5, 3, 3, 3, 3, -5, 3, 3, 3, -5, -5, 3, 3, 3, 3, 3, 3, -5, 3, 3, 3, 3, 3, -5, 3, -5, 3, -5, 3, -5, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 39, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 40, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 41, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 42, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -15, 3, 3, 3, 3, -15, 3, -15, 3, 3, 3, 3, 3, -15, -15, 3, 3, 3, 3, 3, -15, 3, -15, 3, 3, 3, 3, 3, -15, 3, 3, -15, 3, 3, 3, -15, 3, -15, 3, -15, 3, -15, 3, 3, -15, 3, -15, 3, 3, 3, -15, -15, 3, -15, -15, 3, 3, -15, 3, 3, -15, 3, 3, 3, 3, -15, 3, 3, 3, -15, -15, 3, 3, 3, 3, 3, 3, -15, 3, 3, 3, 3, 3, -15, 3, -15, 3, -15, 3, -15, },
{-26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, -26, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 45, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 46, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -2, 3, 3, 3, 3, -2, 3, -2, 3, 3, 3, 3, 3, -2, -2, 3, 3, 3, 3, 3, -2, 3, -2, 3, 3, 3, 3, 3, -2, 3, 3, -2, 3, 3, 3, -2, 3, -2, 3, -2, 3, -2, 3, 3, -2, 3, -2, 3, 3, 3, -2, -2, 3, -2, -2, 3, 3, -2, 3, 3, -2, 3, 3, 3, 3, -2, 3, 3, 3, -2, -2, 3, 3, 3, 3, 3, 3, -2, 3, 3, 3, 3, 3, -2, 3, -2, 3, -2, 3, -2, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 48, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 49, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -18, 3, 3, 3, 3, -18, 3, -18, 3, 3, 3, 3, 3, -18, -18, 3, 3, 3, 3, 3, -18, 3, -18, 3, 3, 3, 3, 3, -18, 3, 3, -18, 3, 3, 3, -18, 3, -18, 3, -18, 3, -18, 3, 3, -18, 3, -18, 3, 3, 3, -18, -18, 3, -18, -18, 3, 3, -18, 3, 3, -18, 3, 3, 3, 3, -18, 3, 3, 3, -18, -18, 3, 3, 3, 3, 3, 3, -18, 3, 3, 3, 3, 3, -18, 3, -18, 3, -18, 3, -18, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 52, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -7, 3, 3, 3, 3, -7, 3, -7, 3, 3, 3, 3, 3, -7, -7, 3, 3, 3, 3, 3, -7, 3, -7, 3, 3, 3, 3, 3, -7, 3, 3, -7, 3, 3, 3, -7, 3, -7, 3, -7, 3, -7, 3, 3, -7, 3, -7, 3, 3, 3, -7, -7, 3, -7, -7, 3, 3, -7, 3, 3, -7, 3, 3, 3, 3, -7, 3, 3, 3, -7, -7, 3, 3, 3, 3, 3, 3, -7, 3, 3, 3, 3, 3, -7, 3, -7, 3, -7, 3, -7, },
{3, 3, -4, 3, 3, 3, 3, -4, 3, -4, 3, 3, 3, 3, 3, -4, -4, 3, 3, 3, 3, 3, -4, 3, -4, 3, 3, 3, 3, 3, -4, 3, 3, -4, 3, 3, 3, -4, 3, -4, 3, -4, 3, -4, 3, 3, -4, 3, -4, 3, 3, 3, -4, -4, 3, -4, -4, 3, 3, -4, 3, 3, -4, 3, 3, 3, 3, -4, 3, 3, 3, -4, -4, 3, 3, 3, 3, 3, 3, -4, 3, 3, 3, 3, 3, -4, 3, -4, 3, -4, 3, -4, },
{-10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, },
{-25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, -25, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 56, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 57, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 58, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 59, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -14, 3, 3, 3, 3, -14, 3, -14, 3, 3, 3, 3, 3, -14, -14, 3, 3, 3, 3, 3, -14, 3, -14, 3, 3, 3, 3, 3, -14, 3, 3, -14, 3, 3, 3, -14, 3, -14, 3, -14, 3, -14, 3, 3, -14, 3, -14, 3, 3, 3, -14, -14, 3, -14, -14, 3, 3, -14, 3, 3, -14, 3, 3, 3, 3, -14, 3, 3, 3, -14, -14, 3, 3, 3, 3, 3, 3, -14, 3, 3, 3, 3, 3, -14, 3, -14, 3, -14, 3, -14, },
{60, 60, -1, 60, 60, 60, 60, 64, 60, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, -1, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, 60, -1, },
{61, 61, -1, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, -1, 61, -1, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 61, -1, },
{61, 61, -1, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 63, 61, -1, 61, -1, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, -1, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 61, 62, 61, -1, },
{-41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, -41, },
{-40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, -40, },
{-27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, -27, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 67, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 68, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -8, 3, 3, 3, 3, -8, 3, -8, 3, 3, 3, 3, 3, -8, -8, 3, 3, 3, 3, 3, -8, 3, -8, 3, 3, 3, 3, 3, -8, 3, 3, -8, 3, 3, 3, -8, 3, -8, 3, -8, 3, -8, 3, 3, -8, 3, -8, 3, 3, 3, -8, -8, 3, -8, -8, 3, 3, -8, 3, 3, -8, 3, 3, 3, 3, -8, 3, 3, 3, -8, -8, 3, 3, 3, 3, 3, 3, -8, 3, 3, 3, 3, 3, -8, 3, -8, 3, -8, 3, -8, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 70, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 71, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 72, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -12, 3, 3, 3, 3, -12, 3, -12, 3, 3, 3, 3, 3, -12, -12, 3, 3, 3, 3, 3, -12, 3, -12, 3, 3, 3, 3, 3, -12, 3, 3, -12, 3, 3, 3, -12, 3, -12, 3, -12, 3, -12, 3, 3, -12, 3, -12, 3, 3, 3, -12, -12, 3, -12, -12, 3, 3, -12, 3, 3, -12, 3, 3, 3, 3, -12, 3, 3, 3, -12, -12, 3, 3, 3, 3, 3, 3, -12, 3, 3, 3, 3, 3, -12, 3, -12, 3, -12, 3, -12, },
{-23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, -23, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 75, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 76, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 77, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 82, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 78, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 79, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 80, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 81, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -6, 3, 3, 3, 3, -6, 3, -6, 3, 3, 3, 3, 3, -6, -6, 3, 3, 3, 3, 3, -6, 3, -6, 3, 3, 3, 3, 3, -6, 3, 3, -6, 3, 3, 3, -6, 3, -6, 3, -6, 3, -6, 3, 3, -6, 3, -6, 3, 3, 3, -6, -6, 3, -6, -6, 3, 3, -6, 3, 3, -6, 3, 3, 3, 3, -6, 3, 3, 3, -6, -6, 3, 3, 3, 3, 3, 3, -6, 3, 3, 3, 3, 3, -6, 3, -6, 3, -6, 3, -6, },
{3, 3, -3, 3, 3, 3, 3, -3, 3, -3, 3, 3, 3, 3, 3, -3, -3, 3, 3, 3, 3, 3, -3, 3, -3, 3, 3, 3, 3, 3, -3, 3, 3, -3, 3, 3, 3, -3, 3, -3, 3, -3, 3, -3, 3, 3, -3, 3, -3, 3, 3, 3, -3, -3, 3, -3, -3, 3, 3, -3, 3, 3, -3, 3, 3, 3, 3, -3, 3, 3, 3, -3, -3, 3, 3, 3, 3, 3, 3, -3, 3, 3, 3, 3, 3, -3, 3, -3, 3, -3, 3, -3, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 84, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 85, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 86, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -38, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, 3, 3, 3, 3, -38, 3, 3, -38, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, 3, 3, -38, 3, -38, 3, 3, 3, -38, -38, 3, -38, -38, 3, 3, -38, 3, 3, -38, 3, 3, 3, 3, -38, 3, 3, 87, -38, -38, 3, 3, 3, 3, 3, 3, -38, 3, 3, 3, 3, 3, -38, 3, -38, 3, -38, 3, -38, },
{3, 3, -13, 3, 3, 3, 3, -13, 3, -13, 3, 3, 3, 3, 3, -13, -13, 3, 3, 3, 3, 3, -13, 3, -13, 3, 3, 3, 3, 3, -13, 3, 3, -13, 3, 3, 3, -13, 3, -13, 3, -13, 3, -13, 3, 3, -13, 3, -13, 3, 3, 3, -13, -13, 3, -13, -13, 3, 3, -13, 3, 3, -13, 3, 3, 3, 3, -13, 3, 3, 3, -13, -13, 3, 3, 3, 3, 3, 3, -13, 3, 3, 3, 3, 3, -13, 3, -13, 3, -13, 3, -13, },
{-39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, -39, },
	};
    
	std::vector<char> nowstr;
	
private:
	int getCharId(char c);

public:
    LEXER() = default;
	Token next(char c);
	int getState() const { return nowState; }
};

extern LEXER lexer;
    