-- phpMyAdmin SQL Dump
-- version 5.1.0
-- https://www.phpmyadmin.net/
--
-- Host: localhost:3306
-- Waktu pembuatan: 30 Bulan Mei 2024 pada 19.53
-- Versi server: 5.7.24
-- Versi PHP: 7.4.15

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `muhammad_adiyat_2210010013`
--

-- --------------------------------------------------------

--
-- Struktur dari tabel `jadwal`
--

CREATE TABLE `jadwal` (
  `id_jadwal` varchar(11) NOT NULL,
  `tgl_jadwal` date NOT NULL,
  `jenis` varchar(50) NOT NULL,
  `total` int(11) NOT NULL,
  `jml` int(11) NOT NULL,
  `id_populasi` varchar(11) NOT NULL,
  `kd_pakan` varchar(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data untuk tabel `jadwal`
--

INSERT INTO `jadwal` (`id_jadwal`, `tgl_jadwal`, `jenis`, `total`, `jml`, `id_populasi`, `kd_pakan`) VALUES
('JAD-001', '2024-06-16', 'Pagi', 30, 5, 'PPL-001', 'PKN-001'),
('JAD-002', '2024-06-16', 'Sore', 25, 5, 'PPL-001', 'PKN-001'),
('JAD-003', '2024-06-16', 'Pagi', 50, 10, 'PPL-002', 'PKN-002');

-- --------------------------------------------------------

--
-- Struktur dari tabel `kandang`
--

CREATE TABLE `kandang` (
  `kd_kandang` varchar(11) NOT NULL,
  `nama_kandang` varchar(50) NOT NULL,
  `kapasitas` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data untuk tabel `kandang`
--

INSERT INTO `kandang` (`kd_kandang`, `nama_kandang`, `kapasitas`) VALUES
('KDG-001', 'Kandang Runtuh', 100),
('KDG-002', 'Kandang Matahari', 300);

-- --------------------------------------------------------

--
-- Struktur dari tabel `pakan`
--

CREATE TABLE `pakan` (
  `kd_pakan` varchar(11) NOT NULL,
  `nama_pakan` varchar(50) NOT NULL,
  `jenis_pakan` varchar(50) NOT NULL,
  `jml_pakan` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data untuk tabel `pakan`
--

INSERT INTO `pakan` (`kd_pakan`, `nama_pakan`, `jenis_pakan`, `jml_pakan`) VALUES
('PKN-001', 'De Heus Layer 4', 'Crumble', 30),
('PKN-002', 'De Heus - Pakan Ayam Pedaging', 'Pelet', 50),
('PKN-003', 'Garda GD-21', 'Mash', 20);

-- --------------------------------------------------------

--
-- Struktur dari tabel `populasi`
--

CREATE TABLE `populasi` (
  `id_populasi` varchar(11) NOT NULL,
  `tgl_populasi` date NOT NULL,
  `jml_mati` int(11) NOT NULL,
  `jml_hidup` int(11) NOT NULL,
  `sisa` int(11) NOT NULL,
  `kd_kandang` varchar(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data untuk tabel `populasi`
--

INSERT INTO `populasi` (`id_populasi`, `tgl_populasi`, `jml_mati`, `jml_hidup`, `sisa`, `kd_kandang`) VALUES
('PPL-001', '2024-06-15', 25, 75, 25, 'KDG-001'),
('PPL-002', '2024-04-12', 20, 250, 50, 'KDG-002');

-- --------------------------------------------------------

--
-- Struktur dari tabel `produksi`
--

CREATE TABLE `produksi` (
  `id_produksi` varchar(11) NOT NULL,
  `tgl_produksi` date NOT NULL,
  `jml_utuh` int(11) NOT NULL,
  `jml_retak` int(11) NOT NULL,
  `total` int(11) NOT NULL,
  `id_populasi` varchar(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data untuk tabel `produksi`
--

INSERT INTO `produksi` (`id_produksi`, `tgl_produksi`, `jml_utuh`, `jml_retak`, `total`, `id_populasi`) VALUES
('PROD-001', '2024-06-16', 100, 20, 120, 'PPL-001'),
('PROD-002', '2024-06-17', 200, 60, 260, 'PPL-002');

--
-- Indexes for dumped tables
--

--
-- Indeks untuk tabel `jadwal`
--
ALTER TABLE `jadwal`
  ADD PRIMARY KEY (`id_jadwal`),
  ADD KEY `id_populasi` (`id_populasi`),
  ADD KEY `kd_pakan` (`kd_pakan`);

--
-- Indeks untuk tabel `kandang`
--
ALTER TABLE `kandang`
  ADD PRIMARY KEY (`kd_kandang`);

--
-- Indeks untuk tabel `pakan`
--
ALTER TABLE `pakan`
  ADD PRIMARY KEY (`kd_pakan`);

--
-- Indeks untuk tabel `populasi`
--
ALTER TABLE `populasi`
  ADD PRIMARY KEY (`id_populasi`),
  ADD KEY `kd_kandang` (`kd_kandang`);

--
-- Indeks untuk tabel `produksi`
--
ALTER TABLE `produksi`
  ADD PRIMARY KEY (`id_produksi`),
  ADD KEY `id_populasi` (`id_populasi`);

--
-- Ketidakleluasaan untuk tabel pelimpahan (Dumped Tables)
--

--
-- Ketidakleluasaan untuk tabel `jadwal`
--
ALTER TABLE `jadwal`
  ADD CONSTRAINT `jadwal_ibfk_1` FOREIGN KEY (`kd_pakan`) REFERENCES `pakan` (`kd_pakan`),
  ADD CONSTRAINT `jadwal_ibfk_2` FOREIGN KEY (`id_populasi`) REFERENCES `populasi` (`id_populasi`);

--
-- Ketidakleluasaan untuk tabel `populasi`
--
ALTER TABLE `populasi`
  ADD CONSTRAINT `populasi_ibfk_1` FOREIGN KEY (`kd_kandang`) REFERENCES `kandang` (`kd_kandang`);

--
-- Ketidakleluasaan untuk tabel `produksi`
--
ALTER TABLE `produksi`
  ADD CONSTRAINT `produksi_ibfk_1` FOREIGN KEY (`id_populasi`) REFERENCES `populasi` (`id_populasi`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
