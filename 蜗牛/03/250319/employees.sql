CREATE TABLE employees (
    emp_no INTEGER PRIMARY KEY,
    birth_date TEXT NOT NULL, 
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    gender TEXT CHECK(gender IN ('M', 'F')) NOT NULL,
    hire_date TEXT NOT NULL
);
 
CREATE TABLE departments (
    dept_no TEXT PRIMARY KEY,
    dept_name TEXT UNIQUE NOT NULL
);
 
CREATE TABLE dept_manager (
    dept_no TEXT NOT NULL,
    emp_no INTEGER NOT NULL,
    from_date TEXT NOT NULL,
    to_date TEXT NOT NULL,
    PRIMARY KEY (emp_no, dept_no),
    FOREIGN KEY (emp_no) REFERENCES employees(emp_no) ON DELETE CASCADE,
    FOREIGN KEY (dept_no) REFERENCES departments(dept_no) ON DELETE CASCADE
);
 
CREATE TABLE dept_emp (
    emp_no INTEGER NOT NULL,
    dept_no TEXT NOT NULL,
    from_date TEXT NOT NULL,
    to_date TEXT NOT NULL,
    PRIMARY KEY (emp_no, dept_no),
    FOREIGN KEY (emp_no) REFERENCES employees(emp_no) ON DELETE CASCADE,
    FOREIGN KEY (dept_no) REFERENCES departments(dept_no) ON DELETE CASCADE
);
 
CREATE TABLE titles (
    emp_no INTEGER NOT NULL,
    title TEXT NOT NULL,
    from_date TEXT NOT NULL,
    to_date TEXT,
    PRIMARY KEY (emp_no, title, from_date),
    FOREIGN KEY (emp_no) REFERENCES employees(emp_no) ON DELETE CASCADE
);
 
CREATE TABLE salaries (
    emp_no INTEGER NOT NULL,
    salary INTEGER NOT NULL,
    from_date TEXT NOT NULL,
    to_date TEXT NOT NULL,
    PRIMARY KEY (emp_no, from_date),
    FOREIGN KEY (emp_no) REFERENCES employees(emp_no) ON DELETE CASCADE
);
 
-- 员工数据
INSERT INTO employees (emp_no, birth_date, first_name, last_name, gender, hire_date) VALUES
(1, '1965-01-01', 'John', 'Doe', 'M', '1990-01-01'),
(2, '1970-02-02', 'Jane', 'Smith', 'F', '1992-03-01'),
(3, '1980-03-15', 'Alice', 'Johnson', 'F', '2015-06-01'),
(4, '1985-04-20', 'Bob', 'Williams', 'M', '2016-07-15'),
(5, '1990-05-25', 'Charlie', 'Brown', 'M', '2018-08-20'),
(6, '1995-06-30', 'David', 'Taylor', 'M', '2020-09-10'),
(7, '2000-07-15', 'Eva', 'Green', 'F', '2021-10-05'),
(8, '2005-08-20', 'Frank', 'White', 'M', '2022-11-15'),
(9, '2010-09-25', 'Grace', 'Black', 'F', '2023-01-01'),
(10, '1982-04-01', 'Heidi', 'Clark', 'F', '2017-02-10'),
(11, '1987-05-05', 'Ivan', 'Davis', 'M', '2019-03-15'),
(12, '1992-06-10', 'Jack', 'Wilson', 'M', '2021-04-20');
 
-- 部门数据
INSERT INTO departments (dept_no, dept_name) VALUES
('d001', 'Sales'),
('d002', 'Engineering'),
('d003', 'Marketing'),
('d004', 'Human Resources'),
('d005', 'Product Development');
 
-- 部门经理数据
INSERT INTO dept_manager (dept_no, emp_no, from_date, to_date) VALUES
('d001', 1, '1990-01-01', '2023-12-31'),
('d002', 2, '1992-03-01', '2023-12-31'),
('d003', 10, '2017-02-10', '2023-12-31'),
('d004', 11, '2019-03-15', '2023-12-31'),
('d005', 12, '2021-04-20', '2023-12-31'); 
 
-- 部门员工数据
INSERT INTO dept_emp (emp_no, dept_no, from_date, to_date) VALUES
(1, 'd001', '1990-01-01', '2000-12-31'),
(2, 'd002', '1992-03-01', '2023-12-31'),
(3, 'd003', '2015-06-01', '2023-12-31'), 
(4, 'd003', '2016-07-15', '2023-12-31'), 
(5, 'd003', '2018-08-20', '2023-12-31'),
(6, 'd004', '2020-09-10', '2023-12-31'), 
(7, 'd004', '2021-10-05', '2023-12-31'), 
(8, 'd005', '2022-11-15', '2023-12-31'), 
(9, 'd005', '2023-01-01', '2023-12-31'), 
(10, 'd003', '2017-02-10', '2023-12-31'), 
(11, 'd004', '2019-03-15', '2023-12-31'), 
(12, 'd005', '2021-04-20', '2023-12-31');

-- 职位数据
INSERT INTO titles (emp_no, title, from_date, to_date) VALUES
(1, 'Manager', '1990-01-01', '2000-12-31'),
(2, 'Manager', '1992-03-01', '2023-12-31'),
(3, 'Staff', '1992-03-01', '2023-12-31'),
(4, 'Engineer', '1990-01-01', '2000-12-31'),
(5, 'Software Engineer', '1992-03-01', '2023-12-31'),
(6, 'Sales Representative', '1990-01-01', '2000-12-31'),
(7, 'Software Engineer', '1992-03-01', '2023-12-31'),
(8, 'Sales Representative', '1990-01-01', '2000-12-31'),
(9, 'Software Engineer', '1992-03-01', '2023-12-31'),
(10, 'Manager', '1990-01-01', '2000-12-31'),
(11, 'Manager', '1992-03-01', '2023-12-31'),
(12, 'Manager', '1990-01-01', '2000-12-31'),
(3, 'Senior Staff', '2024-01-01', '9999-12-31'),
(4, 'Senior Engineer', '2001-01-01', '9999-12-31');

-- 工资数据
INSERT INTO salaries (emp_no, salary, from_date, to_date) VALUES
(1, 50000, '1990-01-01', '2000-12-31'),
(2, 75000, '1992-03-01', '2023-12-31'),
(3, 45000, '2015-06-01', '2023-12-31'),
(4, 47000, '2016-07-15', '2023-12-31'),
(5, 49000, '2018-08-20', '2023-12-31'),
(6, 52000, '2020-09-10', '2023-12-31'),
(7, 50000, '2021-10-05', '2023-12-31'),
(8, 55000, '2022-11-15', '2023-12-31'),
(9, 53000, '2023-01-01', '2023-12-31'),
(10, 60000, '2017-02-10', '2023-12-31'),
(11, 62000, '2019-03-15', '2023-12-31'),
(12, 65000, '2021-04-20', '2023-12-31');
 
 










