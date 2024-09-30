INSERT INTO AsaController.serv_access_logs (real_user_fr, terminalId, rfId, authMode, authType, year, month, day, hour, min, sec, authError, isAuth, created_at, updated_at)
VALUES
( %1, %2, %3, %4, %5, %6, %7, %8, %9, %10, %11, %12, %13, CURRENT_TIMESTAMP, CURRENT_TIMESTAMP )