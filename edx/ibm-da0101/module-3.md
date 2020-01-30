# EDA - Exploratory data analysis
  - feature with most impact on result

# Descriptive Statistics
  - df.describe()
    - mean, std, min, max
  - df["column"].value\_counts()
  - box plot median, 75%, 25%
  - sns.boxplot(x="name", y="name", data=df)
  - scatter plot
    relation between two variables (engine size, price)

# GroupBy
  - df.groupby (categorical variable)
  - df1 = df[["drive-wheels", "body-style", "price"]]
    df_grp = df1.groupby(["drive-wheels", "body-style"], as_index=False).mean
  - pivot table
    df_grp.pivot(index="drive-wheels", columns="body-style")
  - heat map
    multiple variables vs target variable
    plt.pcolor(df_pivot, cmap="RdBu")
    plt.colorbar()
    plt.show()

# Analysis of variace ANOVA
  - correlation of categorical variables
    - F test score
      the ratio of variation between the groups's mean over the variation within each of sample groups
    - p value
      confidence degree - whether the result is statistically significant
  - df\_anova = df[["make", "price"]]
    gr_anova = df_anova.groupby(["make"])
    res = stats.f_oneway(gr_anova.get_group("honda")["price], gr_anova.get_group("subaru")["price"])

# Correlation
  - correlation doesn't mean causation. umbrella and rain
  - engine size and price (positive linear relationship)
  - week relationship. slop ~ 0

# Correlation statistics
  - pearson correlation
    - correlation coefficent
      - ~1 +ve linear
      - ~-1 -ve linear
      - ~0 no relationship

    - p value
      < 0.001 strong
      < 0.05 moderate
      < 0.1 week
      > 0.1 no relation
