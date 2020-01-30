# Data pre-processing/Data cleaning
  - data frame - columnar access

## Handle missing values
  - drop entry
  - replace with avg for numerical values
  - most common for categorical values
  - dataframe.dropna()
    - axis=0 row
    - axis=1 column
    - inplace=True mutate df
  - replace
    mean = df["column"].mean()
    df.replace(np.nan, new_value)

# Data formatting 
  - bringing data to standard format
  - eg: NY, N.Y, NYC -> New York
  - miles/gallon -> metric (km/li)
    df["mpg"] = 235/df["mpg"]
    df.rename(columns={"mpg": "l/100km"}, inplace=True)
  - incorrect data type
    df["price"] = df["price"].astype("int")
    df[["bore", "stroke"]] = df[["bore", "stroke"]].astype("float")

# Data normalization
  - large values influence linear regression
  - simple feature scaling
    x = x / max(x)
  - min max
    x = (x_old - x_min) / (x_max - x_min)
    df["column"] = (df["column"] - df["column"].min()) / (df["column"].max() - df["column"].min())
  - z score
    x = x_old - mean(x) / std_dev(x)
    df["column"] = (df["column] - df["column"].mean()) / df["column"].std()

# Binning
  - group values to bins
  - gives better understanding of data ranges
  - bins = np.linspace(min(df['column']), max(df['column']), 4)
    bin_names = ["low", "medium", "high"]
    df["price-binned"] = pd.cut(df["price"], bins, labels=bin_names, include_lowest=True)

# categorical values to quantitative values
  - statistical models can't handle string values
  - one hot encoding. Add columns gas, diesel
  - pd.get\_dummies(df["fuel"])
    merge dummy values to df
    df = pd.concat([df, dummy_variable_1], axis=1)
    df.drop("fuel-type", axis = 1, inplace=True)
