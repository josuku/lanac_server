SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";

--
-- Base de datos: `lanaccess`
--

-- --------------------------------------------------------

--
-- Estructura de tabla para la tabla `pictures`
--

CREATE TABLE `pictures` (
  `id` int NOT NULL,
  `filename` varchar(100) NOT NULL,
  `operation` int DEFAULT NULL,
  `original_path` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_spanish_ci DEFAULT NULL,
  `processed_path` varchar(500) CHARACTER SET utf8mb4 COLLATE utf8mb4_spanish_ci DEFAULT NULL,
  `created_at` datetime DEFAULT NULL,
  `ip_address` varchar(30) DEFAULT NULL,
  `error` varchar(500) NULL DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_spanish_ci;

-- Índices para tablas volcadas
--

--
-- Indices de la tabla `pictures`
--
ALTER TABLE `pictures`
  ADD PRIMARY KEY (`id`);

--
-- AUTO_INCREMENT de la tabla `pictures`
--
ALTER TABLE `pictures`
  MODIFY `id` int NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=57;
COMMIT;

