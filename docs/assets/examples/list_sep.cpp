#include <string>

#include <lexy/callback.hpp>
#include <lexy/dsl.hpp>
#include <lexy/parse.hpp>
#include <lexy_ext/cfile.hpp>
#include <lexy_ext/report_error.hpp>

namespace dsl = lexy::dsl;

//{
struct production
{
    static constexpr auto rule = [] {
        auto item = dsl::capture(dsl::ascii::alpha);
        auto sep  = dsl::sep(dsl::comma);
        return dsl::list(item, sep);
    }();

    static constexpr auto value = lexy::as_string<std::string>;
};
//}

int main()
{
    auto input  = lexy_ext::read_file<>(stdin);
    auto result = lexy::parse<production>(input, lexy_ext::report_error);
    if (!result.has_value())
        return 1;

    std::printf("The list is: %s\n", result.value().c_str());
    return result ? 0 : 1;
}

