/* 177. Nth Highest Salary
Medium

Write a SQL query to get the nth highest salary from the Employee table.

+----+--------+
| Id | Salary |
+----+--------+
| 1  | 100    |
| 2  | 200    |
| 3  | 300    |
+----+--------+

For example, given the above Employee table, the nth highest salary where n = 2 is 200. If there is no nth highest salary, then the query should return null.

+------------------------+
| getNthHighestSalary(2) |
+------------------------+
| 200                    |
+------------------------+

Accepted
72,996
Submissions
267,886 */

/* Solution from leetcode */
/* 360ms */
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
    IF (
        SELECT COUNT(DISTINCT Salary)
        FROM Employee
    ) < N THEN
        RETURN NULL;
    ELSE
        SET N = N-1;
        RETURN (
            # Write your MySQL query statement below.
            SELECT DISTINCT Salary
            FROM Employee
            ORDER BY Salary DESC
            LIMIT N,1
        );
    END IF;
END

/* Another solution from leetcode. */
/* 173ms < 90% */
CREATE FUNCTION getNthHighestSalary(N INT) RETURNS INT
BEGIN
  SET N = N-1;
  RETURN (
      # Write your MySQL query statement below.      
      select (
          select distinct e.Salary from Employee e order by e.Salary desc limit 1 offset N
      ) as s
  );
END

