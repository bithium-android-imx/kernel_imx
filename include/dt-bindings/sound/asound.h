#ifndef __DT_SOUND_ASOUND_H
#define __DT_SOUND_ASOUND_H

#define	SNDRV_PCM_FORMAT_S8	(0)
#define	SNDRV_PCM_FORMAT_U8	(1)
#define	SNDRV_PCM_FORMAT_S16_LE	(2)
#define	SNDRV_PCM_FORMAT_S16_BE	(3)
#define	SNDRV_PCM_FORMAT_U16_LE	(4)
#define	SNDRV_PCM_FORMAT_U16_BE	(5)
#define	SNDRV_PCM_FORMAT_S24_LE	(6) /* low three bytes */
#define	SNDRV_PCM_FORMAT_S24_BE	(7) /* low three bytes */
#define	SNDRV_PCM_FORMAT_U24_LE	(8) /* low three bytes */
#define	SNDRV_PCM_FORMAT_U24_BE	(9) /* low three bytes */
#define	SNDRV_PCM_FORMAT_S32_LE	(10)
#define	SNDRV_PCM_FORMAT_S32_BE	(11)
#define	SNDRV_PCM_FORMAT_U32_LE	(12)
#define	SNDRV_PCM_FORMAT_U32_BE	(13)
#define	SNDRV_PCM_FORMAT_FLOAT_LE	(14) /* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT_BE	(15) /* 4-byte float, IEEE-754 32-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT64_LE	(16) /* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_FLOAT64_BE	(17) /* 8-byte float, IEEE-754 64-bit, range -1.0 to 1.0 */
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE (18) /* IEC-958 subframe, Little Endian */
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE (19) /* IEC-958 subframe, Big Endian */
#define	SNDRV_PCM_FORMAT_MU_LAW		(20)
#define	SNDRV_PCM_FORMAT_A_LAW		(21)
#define	SNDRV_PCM_FORMAT_IMA_ADPCM	(22)
#define	SNDRV_PCM_FORMAT_MPEG		(23)
#define	SNDRV_PCM_FORMAT_GSM		(24)
#define	SNDRV_PCM_FORMAT_SPECIAL	(31)
#define	SNDRV_PCM_FORMAT_S24_3LE	(32)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S24_3BE	(33)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U24_3LE	(34)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U24_3BE	(35)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S20_3LE	(36)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S20_3BE	(37)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U20_3LE	(38)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U20_3BE	(39)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S18_3LE	(40)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_S18_3BE	(41)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U18_3LE	(42)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_U18_3BE	(43)	/* in three bytes */
#define	SNDRV_PCM_FORMAT_G723_24	(44) /* 8 samples in 3 bytes */
#define	SNDRV_PCM_FORMAT_G723_24_1B	(45) /* 1 sample in 1 byte */
#define	SNDRV_PCM_FORMAT_G723_40	(46) /* 8 Samples in 5 bytes */
#define	SNDRV_PCM_FORMAT_G723_40_1B	(47) /* 1 sample in 1 byte */
#define	SNDRV_PCM_FORMAT_DSD_U8		(48) /* DSD, 1-byte samples DSD (x8) */
#define	SNDRV_PCM_FORMAT_DSD_U16_LE	(49) /* DSD, 2-byte samples DSD (x16), little endian */
#define	SNDRV_PCM_FORMAT_DSD_U32_LE	(50) /* DSD, 4-byte samples DSD (x32), little endian */
#define	SNDRV_PCM_FORMAT_DSD_U16_BE	(51) /* DSD, 2-byte samples DSD (x16), big endian */
#define	SNDRV_PCM_FORMAT_DSD_U32_BE	(52) /* DSD, 4-byte samples DSD (x32), big endian */
#define	SNDRV_PCM_FORMAT_LAST		SNDRV_PCM_FORMAT_DSD_U32_BE

#ifdef SNDRV_LITTLE_ENDIAN
#define	SNDRV_PCM_FORMAT_S16		SNDRV_PCM_FORMAT_S16_LE
#define	SNDRV_PCM_FORMAT_U16		SNDRV_PCM_FORMAT_U16_LE
#define	SNDRV_PCM_FORMAT_S24		SNDRV_PCM_FORMAT_S24_LE
#define	SNDRV_PCM_FORMAT_U24		SNDRV_PCM_FORMAT_U24_LE
#define	SNDRV_PCM_FORMAT_S32		SNDRV_PCM_FORMAT_S32_LE
#define	SNDRV_PCM_FORMAT_U32		SNDRV_PCM_FORMAT_U32_LE
#define	SNDRV_PCM_FORMAT_FLOAT		SNDRV_PCM_FORMAT_FLOAT_LE
#define	SNDRV_PCM_FORMAT_FLOAT64	SNDRV_PCM_FORMAT_FLOAT64_LE
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME SNDRV_PCM_FORMAT_IEC958_SUBFRAME_LE
#endif
#ifdef SNDRV_BIG_ENDIAN
#define	SNDRV_PCM_FORMAT_S16		SNDRV_PCM_FORMAT_S16_BE
#define	SNDRV_PCM_FORMAT_U16		SNDRV_PCM_FORMAT_U16_BE
#define	SNDRV_PCM_FORMAT_S24		SNDRV_PCM_FORMAT_S24_BE
#define	SNDRV_PCM_FORMAT_U24		SNDRV_PCM_FORMAT_U24_BE
#define	SNDRV_PCM_FORMAT_S32		SNDRV_PCM_FORMAT_S32_BE
#define	SNDRV_PCM_FORMAT_U32		SNDRV_PCM_FORMAT_U32_BE
#define	SNDRV_PCM_FORMAT_FLOAT		SNDRV_PCM_FORMAT_FLOAT_BE
#define	SNDRV_PCM_FORMAT_FLOAT64	SNDRV_PCM_FORMAT_FLOAT64_BE
#define	SNDRV_PCM_FORMAT_IEC958_SUBFRAME SNDRV_PCM_FORMAT_IEC958_SUBFRAME_BE
#endif

#endif /* __DT_SOUND_ASOUND_H */
