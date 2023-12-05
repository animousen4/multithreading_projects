package com.animousen4.values;

import lombok.Getter;

import java.util.List;


@Getter
public class CountryTempValues {
    private final List<String> fahrenheitCountries =  List.of("BS", "US", "BZ", "KY", "PW");
    private final List<String> kelvinCountries = List.of("AS", "BS", "KY", "PR");
    private final List<String> celsiusCountries = List.of("RU", "BY", "UA", "PL");
}
