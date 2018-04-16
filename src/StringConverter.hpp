//
// Created by Kane York on 4/16/18.
//

#ifndef ABSTRACTVM_STRINGCONVERTER_HPP
#define ABSTRACTVM_STRINGCONVERTER_HPP

#include <string>

class StringConverter final {
   public:
    StringConverter() = default;

    template <typename V>
    std::string MakeString(V value) const;
};

#endif
