#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>
#include <vector>

static const std::vector<std::string> firstNames
{
  "Ernst", "Friedrich", "Hans", "Heinrich", "Hermann", "Karl", "Otto", "Paul", "Walter", "Wilhelm",
  "Anna", "Bertha", "Elisabeth", "Emma", "Frieda", "Gertrud", "Margarethe", "Maria", "Marie", "Martha",
  "Gerhard", "Gunter", "Heinz", "Helmut", "Herbert", "Kurt", "Werner",
  "Edith", "Elfriede", "Erna", "Gerda", "Hildegard", "Ilse", "Irmgard", "Lieselotte", "Ursula",
  "Alexander", "Christian", "Daniel", "Dennis", "Jan", "Martin", "Michael", "Sebastian", "Stefan", "Thomas",
  "Anja", "Christina", "Julia", "Katrin", "Melanie", "Nadine", "Nicole", "Sabrina", "Sandra", "Stefanie"
};

static const std::vector<std::string> familyNames
{
  "Muller", "Schmidt", "Schneider", "Fischer", "Weber", "Mayer", "Wagner", "Becker", "Schulz",
  "Hoffmann", "Schafer", "Koch", "Bauer", "Richter", "Klein", "Wolf", "Schroder", "Neumann",
  "Schwarz", "Zimmermann", "Braun", "Kruger", "Hofmann", "Hartmann", "Lange", "Schmitt", "Werner",
  "Schmitz", "Krause", "Meier", "Lehmann", "Schmid", "Schulze", "Maier", "Kohler", "Herrmann",
  "Konig", "Walter", "Mayer", "Huber", "Kaiser", "Fuchs", "Peters", "Lang", "Scholz",
  "Moller", "Weis", "Jung", "Hahn", "Schubert", "Vogel", "Friedrich", "Keller", "Gunther",
  "Frank", "Berger", "Winkler", "Roth", "Beck", "Lorenz", "Baumann", "Franke", "Albrecht", "Schuster",
  "Simon", "Ludwig", "Bohm", "Winter", "Kraus", "Martin", "Schumacher", "Kramer", "Vogt",
  "Stein", "Jager", "Otto", "Sommer", "Gros", "Seidel", "Heinrich", "Brandt", "Haas",
  "Schreiber", "Graf", "Schulte", "Dietrich", "Ziegler", "Kuhn", "Pohl", "Engel",
  "Horn", "Busch", "Bergmann", "Thomas", "Voigt", "Sauer", "Arnold", "Wolff", "Pfeiffer", "Foehrkolb"
};

static const std::vector<std::string> delimiters
{
  "-", "_", "."
};

static const std::vector<std::string> services
{
  "mail", "yahoo", "gmail", "yandex", "hotmail", "zoho", "outlook", "fastmail", "hushmail",
  "inbox", "shortmail", "protonmail", "aol", "icloud"
};

static const std::vector<std::string> domainNames
{
  "ac", "ad", "ae", "af", "ag", "ai", "al", "am", "ao", "aq", "ar", "as", "at", "au", "aw", "ax", "az",
  "ba", "bb", "bd", "be", "bf", "bg", "bh", "bi", "bj", "bm", "bn", "bo", "br", "bs", "bt", "bw", "by", "bz",
  "ca", "cc", "cd", "cf", "cg", "ch", "ci", "ck", "cl", "cm", "cn", "co", "cr", "cu", "cv", "cw", "cx", "cy", "cz",
  "de", "dj", "dk", "dm", "do", "dz",
  "ec", "ee", "eg", "er", "es", "et", "eu",
  "fi", "fj", "fk", "fm", "fo", "fr",
  "ga", "gd", "ge", "gf", "gg", "gh", "gi", "gl", "gm", "gn", "gp", "gq", "gr", "gs", "gt", "gu", "gw",  "gy",
  "hk", "hm", "hn", "hr", "ht", "hu",
  "id", "ie", "il", "im", "in", "io", "iq", "ir", "is", "it",
  "je", "jm", "jo", "jp",
  "ke", "kg", "kh", "ki", "km", "kn", "kp", "kr", "kw", "ky", "kz",
  "la", "lb", "lc", "li", "lk", "lr", "ls", "lt", "lu", "lv", "ly",
  "ma", "mc", "md", "me", "mg", "mh", "mk", "ml", "mm", "mn", "mo", "mp", "mq", "mr", "ms", "mt", "mu", "mv", "mw", "mx", "my", "mz",
  "na", "nc", "ne", "nf", "ng", "ni", "nl", "no", "np", "nr", "nu", "nz",
  "om",
  "pa", "pe", "pf", "pg", "ph", "pk", "pl", "pm", "pn", "pr", "ps", "pt", "pw", "py",
  "qa",
  "re", "ro", "rs", "ru", "rw",
  "sa", "sb", "sc", "sd", "se", "sg", "sh", "si", "sk", "sl", "sm", "sn", "so", "sr", "ss", "st", "sv", "sx", "sy", "sz",
  "tc", "td", "tf", "tg", "th", "tj", "tk", "tl", "tm", "tn", "to", "tr", "tt", "tv", "tw", "tz",
  "ua", "ug", "uk", "us", "uy", "uz",
  "va", "vc", "ve", "vg", "vi", "vn", "vu",
  "wf"
};

int main(int argc, char* argv[])
{
  if (argc != 2)
  {
    std::cout << "Usage: generate_sample_file <list_size>\n";
    return 1;
  }


  long int  listSize{};
  try
  {
    listSize = std::stoll(argv[1]);
  }
  catch (...)
  {
    std::cout << "list_size should be integer greater than 0\n";
    return 1;
  }

  std::ofstream outputFile{"email_list.txt"};
  if (!outputFile)
  {
    std::cout << "Could not create output file\n";
    return 1;
  }

  std::srand(std::time(nullptr));

  for (size_t idx{0}; idx < static_cast<size_t>(listSize - 1); ++idx)
  {
    std::stringstream nextEmailStream{};

    auto firstLastNameOrder{std::rand() % 1};

    if (0 == firstLastNameOrder)
    {
      nextEmailStream << firstNames[std::rand() % (firstNames.size())];
      nextEmailStream << delimiters[std::rand() % (delimiters.size())];
      nextEmailStream << familyNames[std::rand() % (familyNames.size())];
    }
    else
    {
      nextEmailStream << familyNames[std::rand() % (familyNames.size())];
      nextEmailStream << delimiters[std::rand() % (delimiters.size())];
      nextEmailStream << firstNames[std::rand() % (firstNames.size())];
    }

    nextEmailStream << "@";

    nextEmailStream << services[rand() % (services.size())];

    nextEmailStream << "." << domainNames[rand() % (domainNames.size())];

    auto emailString{nextEmailStream.str()};

    outputFile << emailString << "\n";
  }

  std::stringstream nextEmailStream{};

  auto firstLastNameOrder{std::rand() % 1};

  if (0 == firstLastNameOrder)
  {
    nextEmailStream << firstNames[std::rand() % (firstNames.size())];
    nextEmailStream << delimiters[std::rand() % (delimiters.size())];
    nextEmailStream << familyNames[std::rand() % (familyNames.size())];
  }
  else
  {
    nextEmailStream << familyNames[std::rand() % (familyNames.size())];
    nextEmailStream << delimiters[std::rand() % (delimiters.size())];
    nextEmailStream << firstNames[std::rand() % (firstNames.size())];
  }

  nextEmailStream << "@";

  nextEmailStream << services[rand() % (services.size())];

  nextEmailStream << "." << domainNames[rand() % (domainNames.size())];

  auto emailString{nextEmailStream.str()};

  outputFile << emailString;

  outputFile.close();



  std::ifstream checkFile{"email_list.txt"};
  if (!outputFile)
  {
    std::cout << "Could not write output file\n";
    return 1;
  }

  return 0;
}
