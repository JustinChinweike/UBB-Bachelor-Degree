%Explanation
%rnd: Generates random numbers from specified distributions (requires the Statistics toolbox).
%rand: Generates uniformly distributed random numbers in the range
%[0,1).
%randn: Generates standard normal distributed random numbers.


% Generate random numbers using rand and randn
uniform_random = rand(1, 10);  % 10 random numbers uniformly distributed in [0, 1)
normal_random = randn(1, 10);  % 10 random numbers from standard normal distribution

% Display generated random numbers
disp('Uniformly distributed random numbers:');
disp(uniform_random);

disp('Normally distributed random numbers:');
disp(normal_random);



%Explanation of Each Line
% 1. rand(1, 10): Generates a 1x10 vector of random numbers
%uniformly distributed in
%[0,1).
%2. randn(1, 10): Generates a 1x10 vector of random numbers following a
%standard normal distribution (
%μ=0,σ=1).
%disp(...): Displays the generated random numbers.

