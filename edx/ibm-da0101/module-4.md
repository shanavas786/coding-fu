# Model development

# Simple and Multiple linear regression
  - SLR one variable
    - y = b0 + b1x
    from sklearn.linear_model import LinearRegression
    lr = LinearRegression()
    lr.fit(df[['highway-mgp']], df['price'])
    lr.intercept\_, lr.coef\_

  - MLR multiple independent variables
    - y = b0 + b1x1 + b2x2 + b3x3 ... + bnxn
    from sklearn.linear_model import LinearRegression
    lr = LinearRegression()
    lr.fit(df[['highway-mgp', 'curb-weight']], df['price'])
    lr.intercept\_, lr.coef\_

# Model evaluation using visualization
  - regression plot
  - residual plot
    sns.residplot(df['mpg'], df['price'])
  - distribution plot


# Polynomial regression
  - independent variables are raised to higher orders
    - fp = np.polyfit(x, y, 3)
      p = polyId(f)
  - multivarable PL

# Measure for In-Sample Evaluation
  - MSE mean square error
    sklearn.metrics.mean_squared_error
  - R2 (Coefficient of Determination)
    how close is the prediction
    R2 = (1 - MSE of live/ MSE or avg data)
    1 = good
    0 = not good
    .r.scoered(x, y)

# Prediction and decision making
