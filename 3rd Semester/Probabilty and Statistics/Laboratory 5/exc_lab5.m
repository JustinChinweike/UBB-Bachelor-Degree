
clear all

x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];

% Input confidence level
conf_level = input("Enter the confidence level (e.g., 0.95): ");
alpha = 1 - conf_level;

% Sample size
n = length(x);

% Sample variance
v = var(x, 1); % Use var(x, 1) for population variance

% Calculate chi-squared critical values
chi2_lower = chi2inv(alpha / 2, n - 1);
chi2_upper = chi2inv(1 - alpha / 2, n - 1);

% Confidence interval for variance
v1 = (n - 1) * v / chi2_upper;
v2 = (n - 1) * v / chi2_lower;

% Display the confidence interval for variance
printf("The %d%% CI for the population variance is (%4.3f, %4.3f).\n", conf_level * 100, v1, v2);

% Optional: Confidence interval for standard deviation
std_lower = sqrt(v1);
std_upper = sqrt(v2);
printf("The %d%% CI for the population standard deviation is (%4.3f, %4.3f).\n", conf_level * 100, std_lower, std_upper);

