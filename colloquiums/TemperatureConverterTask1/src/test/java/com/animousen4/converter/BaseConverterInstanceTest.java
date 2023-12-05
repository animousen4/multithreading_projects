package com.animousen4.converter;

import com.animousen4.values.CountryTempValues;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.junit.jupiter.MockitoExtension;

import java.util.List;
import java.util.Locale;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.instanceOf;
import static org.mockito.Mockito.mock;
import static org.mockito.Mockito.when;


@ExtendWith(MockitoExtension.class)
public class BaseConverterInstanceTest {

    @Test
    void createCelsiusConverterInstanceTest() throws ConverterNotFoundException {
        Locale locale = new Locale("RU", "RU");
        CountryTempValues countryTempValues = mock(CountryTempValues.class);
        when(countryTempValues.getFahrenheitCountries()).thenReturn(List.of());
        when(countryTempValues.getKelvinCountries()).thenReturn(List.of());
        when(countryTempValues.getCelsiusCountries()).thenReturn(List.of("RU"));

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        assertThat(converter, instanceOf(CelsiusConverter.class));
    }

    @Test
    void createKelvinConverterInstanceTest() throws ConverterNotFoundException {
        Locale locale = new Locale("PR", "PR");
        CountryTempValues countryTempValues = mock(CountryTempValues.class);
        when(countryTempValues.getKelvinCountries()).thenReturn(List.of("PR"));

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        assertThat(converter, instanceOf(KelvinConverter.class));
    }

    @Test
    void createFahrenheitConverterInstanceTest() throws ConverterNotFoundException {
        Locale locale = new Locale("BS", "BS");
        CountryTempValues countryTempValues = mock(CountryTempValues.class);

        when(countryTempValues.getKelvinCountries()).thenReturn(List.of());
        when(countryTempValues.getFahrenheitCountries()).thenReturn(List.of("BS"));

        BaseConverter converter = BaseConverter.create(locale, countryTempValues);

        assertThat(converter, instanceOf(FahrenheitConverter.class));
    }
}
