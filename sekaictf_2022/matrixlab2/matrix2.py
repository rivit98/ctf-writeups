# Source Generated with Decompyle++
# File: Matrix_Lab.pyc (Python 3.7)

print('Welcome to Matrix Lab 2! Hope you enjoy the journey.')
print('Lab initializing...')

try:
    import matlab.engine as matlab
    engine = matlab.engine.start_matlab()
    flag = input('Enter the lab passcode: ').strip()
    outcome = False
    if len(flag) == 23 and flag[:6] == 'SEKAI{' and flag[-1:] == '}':
        A = (lambda .0: [ ord(i) ^ 42 for i in .0 ])(flag[6:-1])
        B = matlab.double((lambda .0: [ A[i:i + 4] for i in .0 ])(range(0, len(A), 4)))
        X = (lambda .0: [ list(map(int, i)) for i in .0 ])(engine.magic(4))
        Y = (lambda .0: [ list(map(int, i)) for i in .0 ])(engine.pascal(4))
        C = (lambda .0: [ (lambda .0: [ None for _ in .0 ])(range(len(X))) for _ in .0 ]
)(range(len(X)))
        for i in range(len(X)):
            for j in range(len(X[i])):
                C[i][j] = X[i][j] + Y[i][j]
            
        
        C = matlab.double(C)
        if engine.mtimes(C, engine.rot90(engine.transpose(B), 1337)) == matlab.double([
            [
                2094,
                2962,
                1014,
                2102],
            [
                2172,
                3955,
                1174,
                3266],
            [
                3186,
                4188,
                1462,
                3936],
            [
                3583,
                5995,
                1859,
                5150]]):
            outcome = True
    if outcome:
        print('Access Granted! Your input is the flag.')
    else:
        print('Access Denied! Your flag: SADGE{aHR0cHM6Ly95b3V0dS5iZS9kUXc0dzlXZ1hjUQ==}')
except:
    print('Unknown error. Maybe you are running the lab in an unsupported environment...')
    print('Your flag: SADGE{ovg.yl/2M6pWQB}')

