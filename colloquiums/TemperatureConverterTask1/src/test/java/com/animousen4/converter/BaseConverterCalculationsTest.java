package com.animousen4.converter;

import com.animousen4.values.CountryTempValues;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.List;
import java.util.Locale;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.instanceOf;
import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;


@ExtendWith(MockitoExtension.class)
public class BaseConverterCalculationsTest {

    @Mock
    CountryTempValues countryTempValues;

    @BeforeEach
    void initCountryTempValuesMock() {
        countryTempValues = mock(CountryTempValues.class);
    }

    void initCelsiusMocks() {
        when(countryTempValues.getFahrenheitCountries()).thenReturn(List.of());
        when(countryTempValues.getKelvinCountries()).thenReturn(List.of());
        when(countryTempValues.getCelsiusCountries()).thenReturn(List.of("RU"));
    }

    void initFahrenheitMocks() {
        when(countryTempValues.getKelvinCountries()).thenReturn(List.of());
        when(countryTempValues.getFahrenheitCountries()).thenReturn(List.of("BS"));
    }

    void initKelvinMocks() {
        when(countryTempValues.getKelvinCountries()).thenReturn(List.of("PR"));
    }

    @Test
    void calculateCelsiusConverterCalculationTest() throws ConverterNotFoundException {
        Locale locale = new Locale("RU", "RU");

        initCelsiusMocks();

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        double result = converter.convert(10);

        assertEquals(10, result);
    }

    @Test
    void calculateCelsiusConverterCalculationTestSecond() throws ConverterNotFoundException {
        Locale locale = new Locale("RU", "RU");

        initCelsiusMocks();

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        double result = converter.convert(123);

        assertEquals(123, result);
    }



    @Test
    void calculateKelvinConverterCalculationTest() throws ConverterNotFoundException {
        Locale locale = new Locale("PR", "PR");

        initKelvinMocks();

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        double result = converter.convert(10);

        assertEquals(283.15, result);
    }

    @Test
    void calculateKelvinConverterCalculationTestSecond() throws ConverterNotFoundException {
        Locale locale = new Locale("PR", "PR");

        initKelvinMocks();

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        double result = converter.convert(123);

        assertEquals(396.15, result);
    }

    @Test
    void calculateFahrenheitConverterCalculationTest() throws ConverterNotFoundException {
        Locale locale = new Locale("BS", "BS");

        initFahrenheitMocks();

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        double result = converter.convert(10);

        assertEquals(50, result);

    }

    @Test
    void calculateFahrenheitConverterCalculationTestSecond() throws ConverterNotFoundException {
        Locale locale = new Locale("BS", "BS");

        initFahrenheitMocks();

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        double result = converter.convert(123);

        assertEquals(253.4, result);

    }


}
