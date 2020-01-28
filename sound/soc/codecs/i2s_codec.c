/*
 * i2s_codec.c  --  Generic I2S ALSA SoC Audio driver
 *
 * Copyright 2020-2011 Freescale Semiconductor, Inc. All Rights Reserved.
 * Copyright 2020 Bithium S.A. All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/pm.h>
#include <linux/clk.h>
#include <linux/log2.h>
#include <linux/regmap.h>
#include <linux/regulator/driver.h>
#include <linux/regulator/machine.h>
#include <linux/regulator/consumer.h>
#include <linux/of_device.h>
#include <sound/core.h>
#include <sound/tlv.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>
#include <sound/soc-dapm.h>
#include <sound/initval.h>

static const struct snd_soc_dapm_widget i2s_codec_dapm_widgets[] = {
   SND_SOC_DAPM_INPUT("LINE_IN"),
   SND_SOC_DAPM_OUTPUT("LINE_OUT"),
};

/* routes for i2s_codec */
static const struct snd_soc_dapm_route i2s_codec_dapm_routes[] = {
   {"Capture", NULL, "LINE_IN"}, /* line_in --> adc_mux */
   {"LINE_OUT", NULL, "Playback"},
};

static const struct snd_kcontrol_new i2s_codec_snd_controls[] = {
   /* SOC_DOUBLE_S8_TLV with invert */
   {
      .iface = SNDRV_CTL_ELEM_IFACE_PCM,
      .name = "PCM Playback Volume",
      .access = SNDRV_CTL_ELEM_ACCESS_INACTIVE,
      .info = NULL,
      .get = NULL,
      .put = NULL,
   }
};

static const struct snd_soc_dai_ops i2s_codec_ops = {
   .hw_params = NULL,
   .digital_mute = NULL,
   .set_fmt = NULL,
};

static struct snd_soc_dai_driver i2s_codec_dai = {
   .name = "i2s_codec",
   .playback = {
      .stream_name = "Playback",
      .channels_min = 1,
      .channels_max = 2,
      .rates = -1,
      .formats = -1,
   },
   .capture = {
      .stream_name = "Capture",
      .channels_min = 1,
      .channels_max = 2,
      .rates = -1,
      .formats = -1,
   },
   .ops = &i2s_codec_ops,
   .symmetric_rates = 1,
};

static struct snd_soc_codec_driver i2s_codec_driver = {
   .component_driver = {
      .controls         = i2s_codec_snd_controls,
      .num_controls     = ARRAY_SIZE(i2s_codec_snd_controls),
      .dapm_widgets     = i2s_codec_dapm_widgets,
      .num_dapm_widgets = ARRAY_SIZE(i2s_codec_dapm_widgets),
      .dapm_routes      = i2s_codec_dapm_routes,
      .num_dapm_routes  = ARRAY_SIZE(i2s_codec_dapm_routes),
   },
};

static int i2s_codec_codec_probe(struct platform_device *pdev)
{
   struct device *dev = &pdev->dev;
   int ret;

   dev_info(dev, "i2s_codec probe start\n");

   int rate = 0;
   ret = of_property_read_u32(dev->of_node, "rate", &rate);
   if(ret) {
      dev_err(dev, "%s: read supported rate from device tree failed (%d)\n",
              __func__, ret);
      return ret;
   }

   i2s_codec_dai.capture.rates = i2s_codec_dai.playback.rates = rate;

   int format = 0;
   ret = of_property_read_u32(dev->of_node, "format", &format);
   if(ret) {
      dev_err(dev, "%s: read supported format from device tree failed (%d)\n",
              __func__, ret);
      return ret;
   }

   i2s_codec_dai.capture.formats = i2s_codec_dai.playback.formats = rate;

   ret = snd_soc_register_codec(dev, &i2s_codec_driver, &i2s_codec_dai, 1);

   if (ret) {
      dev_err(dev, "%s: snd_soc_register_codec() failed (%d)\n",
         __func__, ret);
      return ret;
   }

   dev_info(dev, "i2s_codec probe exit %x\n", ret);
   return ret;
}

static int i2s_codec_codec_remove(struct platform_device *pdev)
{
   snd_soc_unregister_codec(&pdev->dev);
   return 0;
}

static const struct of_device_id i2s_codec_dt_ids[] = {
	{ .compatible = "fsl,i2s_codec", },
	{ /* sentinel */ }
};
MODULE_DEVICE_TABLE(of, i2s_codec_dt_ids);

static struct platform_driver i2s_codec_codec_driver = {
   .driver = {
      .name = "i2s_codec",
      .of_match_table = i2s_codec_dt_ids,
   },
   .probe = i2s_codec_codec_probe,
   .remove = i2s_codec_codec_remove,
};

module_platform_driver(i2s_codec_codec_driver);

MODULE_DESCRIPTION("Generic I2S ALSA SoC Codec Driver");
MODULE_AUTHOR("Alexandre Sousa <alexandre.sousa@bithium.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:i2s_codec");
