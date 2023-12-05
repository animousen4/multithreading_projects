package com.animousen4.converter;

import com.animousen4.values.CountryTempValues;

import java.util.Locale;

public abstract class BaseConverter {
    public abstract double convert(double celsius);

    public static BaseConverter create(Locale locale, CountryTempValues countryTempValues) throws ConverterNotFoundException {
        String countryCode = locale.getCountry();
        if (countryTempValues.getKelvinCountries().contains(countryCode))
            return new KelvinConverter();
        else
            if (countryTempValues.getFahrenheitCountries().contains(countryCode))
                return new FahrenheitConverter();
            else
                if (countryTempValues.getCelsiusCountries().contains(countryCode))
                    return new CelsiusConverter();
                else
                    throw new ConverterNotFoundException();
    }
}

class CelsiusConverter extends BaseConverter {
    public double convert(double celsius) {
        return celsius;
    }
}

class KelvinConverter extends BaseConverter {
    public double convert(double celsius) {
        return celsius + 273.15;
    }
}

class FahrenheitConverter extends BaseConverter {
    public double convert(double celsius) {
        return celsius * 9 / 5 + 32;
    }
}
